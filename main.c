#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int server_socket;

// Function to handle termination signals
void handle_signal(int signal) {
    if (signal == SIGINT) {
        printf("\nShutting down server...\n");
        close(server_socket); // Close the server socket
        exit(0); // Exit the program
    }
}

// Function to determine the content type based on file extension
const char* get_content_type(const char *file_path) {
    if (strstr(file_path, ".txt")) {
        return "text/plain";
    } else if (strstr(file_path, ".html")) {
        return "text/html";
    } else if (strstr(file_path, ".json")) {
        return "application/json";
    }
    return "application/octet-stream"; // Default for unknown types
}

// Function to send a response
void send_response(int client_socket, const char *status, const char *content_type, const char *body) {
    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 %s\r\n"
                      "Content-Type: %s\r\n"
                      "Content-Length: %zu\r\n"
                      "Connection: close\r\n"
                      "\r\n"
                      "%s", status, content_type, strlen(body), body);
    send(client_socket, response, strlen(response), 0);
}

// Function to serve static files
void serve_file(int client_socket, const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        send_response(client_socket, "404 Not Found", "text/plain", "File not found here");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_content = malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
    fclose(file);

    const char *content_type = get_content_type(file_path);
    send_response(client_socket, "200 OK", content_type, file_content);
    free(file_content);
}

// Main function
int main() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Set up signal handling
    signal(SIGINT, handle_signal);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Before binding the socket. To refresh connection to port in OS.
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_socket);
        return 1;
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // inet_pton(AF_INET, "192.168.1.100", &server_addr.sin_addr); // Bind to specific IP
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        return 1;
    }

    // Listen for incoming connections
    listen(server_socket, 3);
    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Accept a client connection
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        // Read the request
        char buffer[BUFFER_SIZE];
        read(client_socket, buffer, BUFFER_SIZE - 1);
        buffer[BUFFER_SIZE - 1] = '\0';

        // Simple request parsing
        // printf("Received request: %s\n", buffer); // Debugging output
        if (strncmp(buffer, "GET /file1.txt HTTP/1.1", 23) == 0) {
            serve_file(client_socket, "./files/file1.txt");
        } else if (strncmp(buffer, "GET /file2.html HTTP/1.1", 24) == 0) {
            serve_file(client_socket, "./files/file2.html");
        } else if (strncmp(buffer, "GET /file3.json HTTP/1.1", 24) == 0) {
            serve_file(client_socket, "./files/file3.json");
        } else {
            send_response(client_socket, "404 Not Found", "text/plain", "File not found one");
        }

        // Close the client socket
        close(client_socket);
    }

    // Close the server socket (this line will be reached only if the loop is exited)
    close(server_socket);
    return 0;
}