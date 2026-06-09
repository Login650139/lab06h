# Лабораторная работа №6 tutorial
Сборка
<pre>
[ 33%] Building CXX object banking/CMakeFiles/banking.dir/Account.cpp.o
[ 66%] Building CXX object banking/CMakeFiles/banking.dir/Transaction.cpp.o
[100%] Linking CXX static library libbanking.a
[100%] Built target banking</pre>

## Настройка пользователя

```bash
git config --global user.name "Login650139"
git config --global user.email "d7445580@gmail.com"
```

Указывает имя пользователя и почту для будущих коммитов.

```bash
alias gsed=sed
```

Создаёт короткое имя `gsed` для команды `sed`.

## Клонирование предыдущей лабораторной работы

```bash
cd "/home/vboxuser/Рабочий стол/project/projects"
mkdir -p Login650139_labs
cd Login650139_labs
rm -rf lab06tut
git clone https://github.com/Login650139/lab05.git lab06tut
cd lab06tut
```

Клонирует репозиторий `lab05` в новую папку `lab06tut`.

```bash
git remote remove origin
git remote add origin https://github.com/Login650139/lab06tut.git
git branch -M main
```

Удаляет старую ссылку на репозиторий и добавляет новый репозиторий `lab06tut`.

## Добавление версии проекта

```bash
python3 - <<'PY'
from pathlib import Path

p = Path("CMakeLists.txt")
text = p.read_text()

insert = '''project(print)

set(PRINT_VERSION_MAJOR 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)

set(PRINT_VERSION
    ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK}
)

set(PRINT_VERSION_STRING "v${PRINT_VERSION}")
'''

text = text.replace("project(print)", insert)

if "include(CPackConfig.cmake)" not in text:
    text += "\ninclude(CPackConfig.cmake)\n"

p.write_text(text)
PY
```

Добавляет в `CMakeLists.txt` номер версии проекта и подключает файл настройки CPack.

```bash
git diff
```

Показывает изменения, которые были внесены в файлы.

## Создание файлов описания пакета

```bash
cat > DESCRIPTION <<'EOF'
Static C++ library for printing text to output streams.
EOF
```

Создаёт описание пакета.

```bash
cat > LICENSE <<'EOF'
MIT License
EOF
```

Создаёт файл лицензии.

```bash
export DATE="`LANG=en_US date +'%a %b %d %Y'`"
```

Сохраняет текущую дату в переменную `DATE`.

```bash
cat > ChangeLog.md <<EOF
* ${DATE} Login650139 <d7445580@gmail.com> 0.1.0.0
- Added CPack package configuration
EOF
```

Создаёт файл истории изменений для пакета.

## Настройка CPack

```bash
cat > CPackConfig.cmake <<'EOF'
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "print")
set(CPACK_PACKAGE_CONTACT "d7445580@gmail.com")

set(CPACK_PACKAGE_VERSION_MAJOR ${PRINT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION ${PRINT_VERSION})

set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing")

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")

set(CPACK_RPM_PACKAGE_NAME "print-devel")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_CHANGELOG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)
set(CPACK_RPM_FILE_NAME RPM-DEFAULT)

set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Login650139 <d7445580@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

include(CPack)
EOF
```

Создаёт конфигурацию CPack для сборки пакетов `.tar.gz`, `.zip`, `.deb` и `.rpm`.

## Gitignore

```bash
cat > .gitignore <<'EOF'
_build/
artifacts/
*.o
*.a
CMakeCache.txt
CMakeFiles/
cmake_install.cmake
Makefile
EOF
```

Добавляет временные файлы сборки в игнор Git.

## Локальная сборка

```bash
rm -rf _build artifacts
```

Удаляет старые результаты сборки.

```bash
cmake -S . -B _build
```

Конфигурирует проект CMake в папку `_build`.

```bash
cmake --build _build
```

Собирает проект.

```bash
mkdir -p artifacts
```

Создаёт папку для готовых пакетов.

```bash
cpack --config _build/CPackConfig.cmake -G TGZ -B artifacts
```

Создаёт архивный пакет `.tar.gz`.

```bash
tree artifacts
```

Показывает созданные пакеты.

## GitHub Actions

```bash
mkdir -p .github/workflows
```

Создаёт папку для workflow GitHub Actions.

```bash
cat > .github/workflows/package.yml <<'EOF'
name: Package

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
  build:
    name: build and package
    runs-on: ubuntu-latest

    steps:
      - name: Checkout repository
        uses: actions/checkout@v4

      - name: Install tools
        run: |
          sudo apt-get update
          sudo apt-get install -y cmake g++ rpm zip

      - name: Configure
        run: |
          cmake -S . -B _build -DCMAKE_BUILD_TYPE=Release

      - name: Build
        run: |
          cmake --build _build --config Release

      - name: Create packages
        run: |
          mkdir -p artifacts
          cpack --config _build/CPackConfig.cmake -G TGZ -B artifacts
          cpack --config _build/CPackConfig.cmake -G ZIP -B artifacts
          cpack --config _build/CPackConfig.cmake -G DEB -B artifacts
          cpack --config _build/CPackConfig.cmake -G RPM -B artifacts
          ls -la artifacts

      - name: Upload workflow artifacts
        uses: actions/upload-artifact@v4
        with:
          name: lab06tut-packages
          path: artifacts/*

      - name: Create GitHub Release
        if: startsWith(github.ref, 'refs/tags/')
        env:
          GH_TOKEN: ${{ github.token }}
        run: |
          gh release view "$GITHUB_REF_NAME" || gh release create "$GITHUB_REF_NAME" --title "$GITHUB_REF_NAME" --notes "Release $GITHUB_REF_NAME"

      - name: Upload packages to Release
        if: startsWith(github.ref, 'refs/tags/')
        env:
          GH_TOKEN: ${{ github.token }}
        run: |
          find artifacts -maxdepth 1 -type f -exec gh release upload "$GITHUB_REF_NAME" {} --clobber \;
EOF
```

Создаёт GitHub Actions workflow. Он собирает проект, создаёт пакеты и при наличии тега загружает их в GitHub Releases.

## Коммит и отправка

```bash
git status
```

Показывает изменённые файлы.

```bash
git add .
```

Добавляет все изменения в индекс Git.

```bash
git commit -m "added cpack config and github actions"
```

Создаёт коммит с настройкой CPack и GitHub Actions.

```bash
git tag v0.1.0.0
```

Создаёт тег версии.

```bash
git push -u origin main --tags
```

Отправляет коммит и тег в репозиторий GitHub.
