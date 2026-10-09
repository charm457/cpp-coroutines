# Qt Клавиатура (`qt_klav`)

Подробная инструкция: как установить инструменты, собрать и запустить проект.

---

## 1. Установка (один раз)

Нужен **MSYS2** с окружением **ucrt64** — в нём лежат gcc, cmake, ninja и Qt6.

1. Если MSYS2 ещё не установлен — скачайте и установите: <https://www.msys2.org/>
2. Откройте **MSYS2 UCRT64** и выполните команды **по очереди** (они тяжёлые):
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
   pacman -S mingw-w64-ucrt-x86_64-qt6
   ```
3. Добавьте каталог MSYS2 в переменную среды **PATH**:
   - `Win + R` → `sysdm.cpl` → вкладка **Дополнительно** → **Переменные среды**;
   - в блоке **Системные переменные** выберите `Path` → **Изменить** → **Создать**;
   - впишите: `C:\msys64\ucrt64\bin`
   - нажмите ОК во всех окнах.

   > ⚠️ Строка `C:\msys64\ucrt64\bin` должна стоять **выше** `C:\Users\byzov\gcc\bin`,
   > иначе CMake возьмёт «чужой» gcc и Qt6 не найдёт.

4. **Перезапустите терминал/VS Code**, чтобы PATH подхватился, и проверьте:
   ```powershell
   where.exe gcc      # первый путь должен быть C:\msys64\ucrt64\bin\gcc.exe
   where.exe cmake    # первый путь должен быть C:\msys64\ucrt64\bin\cmake.exe
   where.exe ninja
   where.exe qmake6   # появится после установки qt6
   ```

> Скрипты `build.bat` и `run.bat` **сами** добавляют `C:\msys64\ucrt64\bin` в PATH,
> поэтому проект соберётся и запустится даже без правки переменных среды.

---

## 2. Сборка

**Вариант А (простой):** запустите двойным кликом
`c:\cpp-coroutines\qt_klav\build.bat`

**Вариант Б (вручную в терминале):**
```powershell
cd c:\cpp-coroutines\qt_klav
.\build.bat
```

Что делает скрипт:
1. создаёт папку `build_ninja\`;
2. `cmake -G Ninja ..` — генерирует ninja-файлы (ищет Qt6);
3. `cmake --build .` — компилирует → появится `build_ninja\keyboard.exe`;
4. копирует картинку: `img\grustnii-smail.png` → `build_ninja\img\`.

Проверка: файл `c:\cpp-coroutines\qt_klav\build_ninja\keyboard.exe` существует.

---

## 3. Запуск

**Вариант А (простой):** запустите двойным кликом
`c:\cpp-coroutines\qt_klav\run.bat`

**Вариант Б (вручную):**
```powershell
cd c:\cpp-coroutines\qt_klav\build_ninja
# PATH с Qt из MSYS2 должен быть добавлен (см. раздел 1, шаг 3)
.\keyboard.exe
```

> ⚠️ Запускать **именно из папки `build_ninja`** — иначе программа не найдёт
> картинку `img/grustnii-smail.png` и смайлик не отобразится.

Запуск из IDE: откройте папку `c:\cpp-coroutines\qt_klav` в VS Code,
дождитесь выбора Kit с Qt6 (MSYS2 ucrt64) и нажмите F5 / Run.

---

## 4. Как пользоваться

Окно **«Грустная Клавиатура»**: сверху смайлик, ниже строка текста, внизу экранная клавиатура.

Работает **физическими клавишами** (окно должно быть активным — кликните по нему):

| Клавиша | Что делает |
|---|---|
| Буквы `A`–`Z` (раскладка любая) | вводят русские буквы (`Ф`, `Ы`, `В`…) |
| Цифры `0`–`9`, `-`, `=`, `\`, `,`, `.`, `` ` `` | вводят символы |
| `Пробел` | вставляет пробел |
| `Enter` | перенос строки |
| `Backspace` (Удалить) | удаляет последний символ (можно зажать) |

Одновременно подсвечивается (анимируется) соответствующая кнопка на экранной клавиатуре.

---

### Linux (bash)

**Сборка:**
```bash
cd /путь/к/cpp-coroutines/qt_klav
chmod +x build.sh run.sh   # один раз
./build.sh
```

**Запуск:**
```bash
./run.sh
```

Нужен Qt6 для разработки:
- Debian/Ubuntu: `sudo apt install cmake ninja-build qt6-base-dev`
- Arch: `sudo pacman -S cmake ninja qt6-base`

Нет `ninja` — скрипт сам соберёт через обычные makefiles.

---

## 5. Если что-то пошло не так

| Симптом | Причина / решение |
|---|---|
| `CMake Error: Could not find a package configuration file ... Qt6Config.cmake` | В PATH не `C:\msys64\ucrt64\bin`, либо не установлен пакет `mingw-w64-ucrt-x86_64-qt6` |
| `ninja: command not found` / `Unknown generator` | Не установлен ninja или не добавлен PATH |
| `keyboard.exe` не стартует (ошибка 0xc0000135) | Не видит DLL Qt — добавьте `C:\msys64\ucrt64\bin` в PATH и запустите через `run.bat` |
| Смайлик не отображается | Программа запущена не из папки `build_ninja` |
| Клавиши не вводят текст | Окно неактивно — кликните по окну мышкой |
| Ошибка про `c++` не найден | В PATH первый `c++` не из MSYS2 — см. раздел 1, шаг 3 |
| `./build.sh: Permission denied` | Выполните один раз `chmod +x build.sh run.sh` |
| `Could not find Qt6Config.cmake` (Linux) | Нет пакета Qt6 — `sudo apt install qt6-base-dev` (см. раздел 4) |
| Красные подчёркивания в VS Code | IntelliSense не видит Qt: `Ctrl+Shift+P` → «Developer: Reload Window» (см. `.vscode/c_cpp_properties.json`) |