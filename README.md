# Лабораторная работа №6 Homework

## Цель

Настроить автоматическую сборку приложения `solver` и создание пакетов через GitHub Actions.

## Подготовка проекта

Проект был создан на основе `lab06tut`:

```bash
git clone https://github.com/Login650139/lab06tut.git lab06h
cd lab06h
git remote remove origin
git remote add origin https://github.com/Login650139/lab06h.git
```

Команды клонируют предыдущую лабораторную работу и подключают новый репозиторий `lab06h`.

## Приложение solver

Был создан файл:

```bash
solver_application/solver.cpp
```

Программа принимает два катета прямоугольного треугольника и считает гипотенузу по теореме Пифагора:

```cpp
double c = std::sqrt(a * a + b * b);
```

Проверка работы:

```bash
echo "3 4" | ./_build/solver
```

Результат:

```text
c = 5
```

## CMake

В `CMakeLists.txt` добавлена сборка исполняемого файла:

```cmake
add_executable(solver
    solver_application/solver.cpp
)

install(TARGETS solver
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)
```

Команда `add_executable` создаёт приложение `solver`, а `install` указывает, что оно должно попадать внутрь пакетов.

## CPack

Для настройки пакетов был создан файл `CPackConfig.cmake`.

В нём указаны имя пакета, версия, описание, лицензия и параметры для разных форматов:

```cmake
set(CPACK_PACKAGE_NAME "solver")
set(CPACK_DEBIAN_PACKAGE_NAME "solver")
set(CPACK_RPM_PACKAGE_NAME "solver")
set(CPACK_WIX_UPGRADE_GUID "51F3E6B3-6F1B-4B52-94B8-9C59C1A1F6A1")
set(CPACK_DMG_VOLUME_NAME "solver")
```

Эти настройки нужны для создания `.deb`, `.rpm`, `.msi`, `.dmg`, `.tar.gz` и `.zip`.

## GitHub Actions

Для CI был создан файл:

```bash
.github/workflows/release.yml
```

Содержимое workflow:

```yaml
name: Release packages

on:
  push:
    branches:
      - main
    tags:
      - "v*"
  pull_request:
    branches:
      - main
  workflow_dispatch:

permissions:
  contents: write

jobs:
  build-test:
    name: build and test
    runs-on: ubuntu-latest

    steps:
      - name: Checkout repository
        uses: actions/checkout@v4

      - name: Install tools
        run: sudo apt-get update && sudo apt-get install -y cmake g++

      - name: Configure
        run: cmake -S . -B _build -DCMAKE_BUILD_TYPE=Release

      - name: Build
        run: cmake --build _build --config Release

      - name: Run solver
        run: echo "3 4" | ./_build/solver

  package-linux:
    name: package Linux DEB RPM TGZ ZIP
    runs-on: ubuntu-latest
    if: startsWith(github.ref, 'refs/tags/')

    steps:
      - name: Checkout repository
        uses: actions/checkout@v4

      - name: Install tools
        run: sudo apt-get update && sudo apt-get install -y cmake g++ rpm zip

      - name: Configure
        run: cmake -S . -B _build -DCMAKE_BUILD_TYPE=Release

      - name: Build
        run: cmake --build _build --config Release

      - name: Create packages
        run: |
          mkdir -p packages
          cpack --config _build/CPackConfig.cmake -G DEB -B packages
          cpack --config _build/CPackConfig.cmake -G RPM -B packages
          cpack --config _build/CPackConfig.cmake -G TGZ -B packages
          cpack --config _build/CPackConfig.cmake -G ZIP -B packages
```

Workflow автоматически собирает проект, запускает проверку приложения и при создании тега собирает пакеты.

## Проверка

Локальная проверка выполнялась командами:

```bash
cmake -S . -B _build -DCMAKE_BUILD_TYPE=Release
cmake --build _build
echo "3 4" | ./_build/solver
cpack --config _build/CPackConfig.cmake -G TGZ -B artifacts
```

## Отправка на GitHub

```bash
git add .
git commit -m "complete lab06 homework packaging"
git tag v0.1.2
git push -u origin main --tags
```

Команды фиксируют изменения, создают тег версии и отправляют проект на GitHub. После push GitHub Actions запускает сборку и создаёт release-пакеты.
