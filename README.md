[![CI Linux](https://github.com/dmitriysd9202/lab04/actions/workflows/linux.yml/badge.svg)](https://github.com/dmitriysd9202/lab04/actions/workflows/linux.yml)
# Laboratory Work №4

## Тема
Системы непрерывной интеграции на примере GitHub Actions.

## Цель
Изучить принципы непрерывной интеграции и настроить автоматическую сборку CMake-проекта на платформах Linux и Windows с использованием GitHub Actions.

## Задачи
- Создать публичный репозиторий `lab04` на основе проекта из лабораторной работы №3.
- Ознакомиться с предоставленными учебными материалами.
- Настроить непрерывную интеграцию через GitHub Actions: создать workflow для сборки на Linux с компиляторами GCC и Clang, а также на Windows с компилятором MSVC.
- Добавить бейдж состояния сборки в файл `README.md`.
- Зафиксировать все выполненные команды в файле `vivod.txt`.
- Оформить отчет и отправить ссылку на репозиторий в Slack.

## Ход работы

В данной работе действия выполняются на GitHub Actions

### 1. Создание репозитория
Создал публичный репозиторий `lab04` через веб-интерфейс GitHub, не устанавливая дополнительных утилит.

### 2. Перенос проекта из lab03
Для продолжения работы мне потребовалась актуальная копия проекта из лабораторной работы №3. Я клонировал репозиторий `lab03` локально и привязал его к новому origin:

```bash
export GITHUB_USERNAME=dmitriysd9202
git clone https://github.com/${GITHUB_USERNAME}/lab03 projects/lab04
cd projects/lab04
git remote remove origin
git remote add origin https://github.com/${GITHUB_USERNAME}/lab04.git
```

### 3. Создание workflow для GitHub Actions
В корне проекта я создал директорию .github/workflows, в которой разместил два YAML-файла с описанием сборочных процессов.

### 3.1. Workflow для Linux (linux.yml)
Этот файл описывает сборку на последней версии Ubuntu с использованием двух компиляторов: GCC и Clang. Стратегия матрицы позволяет запустить параллельные задачи для каждого инструментa.

```yaml
name: Linux CI

on:
  push:
    branches: [  main ]
  pull_request:
    branches: [  main ]

jobs:
  build:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        compiler: [ gcc, clang ]
    steps:
      - uses: actions/checkout@v3
      - name: Configure CMake
        env:
          CC: ${{ matrix.compiler }}
          CXX: ${{ (matrix.compiler == 'clang') && 'clang++' || 'g++' }}
        run: cmake -B build -S .
      - name: Build
        run: cmake --build build
```

### 3.2. Workflow для Windows (windows.yml)
Файл отвечает за сборку на Windows с компилятором MSVC, который устанавливается по умолчанию в образе windows-latest.

```yaml
name: Windows CI

on:
  push:
    branches: [  main ]
  pull_request:
    branches: [  main ]

jobs:
  build:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v3
      - name: Configure CMake
        run: cmake -B build -S .
      - name: Build
        run: cmake --build build
```


### 4. Добавление бейджа статуса сборки
Чтобы быстро оценивать состояние проекта, я добавил в начало README.md бейдж сборки для Linux:

```bash
BADGE="[![CI Linux](https://github.com/${GITHUB_USERNAME}/lab04/actions/workflows/linux.yml/badge.svg)](https://github.com/${GITHUB_USERNAME}/lab04/actions/workflows/linux.yml)"
echo "$BADGE" > tmp_badge.md
cat README.md >> tmp_badge.md
mv tmp_badge.md README.md
```

### 5. Публикация изменений
Все созданные файлы были добавлены в отслеживание Git, закоммичены и отправлены на GitHub:

```bash
git add .
git commit -m "add workflows (GitHub actions)"
git push origin main
```

### 6. Запись сессии команд
Для документирования всех выполненных действий я использовал утилиту script, которая сохранила ввод и вывод терминала в файл vivod.txt . Этот файл также размещён в репозитории.
