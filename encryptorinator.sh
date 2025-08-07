#!/bin/bash
# Проверка наличия исполняемого файла
if [ ! -f "./encryptorinator" ]; then #компилировать заранее, указывать имя out
    echo "Ошибка: файл 'text_processor' не найден!"
    exit 1
fi

# Обработка ввода
if [ $# -eq 0 ]; then
    # Режим stdin
    ./encryptorinator
else
    # Режим аргументов (объединяем все аргументы в одну строку)
    echo "$*" | ./encryptorinator
fi