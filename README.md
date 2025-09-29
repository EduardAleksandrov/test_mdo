[![C](https://img.shields.io/badge/C-f06529)](https://en.wikipedia.org/wiki/C_(programming_language))
[![HTTP](https://img.shields.io/badge/HTTP-f0db4f)](https://en.wikipedia.org/wiki/HTTP)

# C _ project

## Задание
- Однопоточный HTTP сервер для обработки запросов.

- Посмотреть задание [link](./task/task.md)

## Установка и запуск программы

1) При первом запуске создаем папку build в корне проекта ```mkdir build```

2) Запускаем проект в Linux: ```./load.sh all```

3) Запускаем проект в Windows:

- ```cd build``` далее ```cmake ..``` далее ```cmake --build . --config Release``` далее ```.\http_server.exe```

## Проверка

Открыть браузер и запустить запросы:
- ```http://localhost:8080/file1.txt```
- ```http://localhost:8080/file2.html```
- ```http://localhost:8080/file3.json```
