@ECHO OFF
:: Leitura do versao a partir do arquivo info.json
for /f "tokens=2 delims=:," %%a in ('type info.json ^| findstr /C:"\"version\""') do (
    set "versao=%%~a"
)

:: Remove espaços em branco ao redor do versao
set "versao=%versao: =%"
set "versao=%versao:~1,-1%"

:: Verifica se o versao foi obtido corretamente
if "%versao%"=="" (
    echo Erro: Falha ao obter o nome do arquivo info.json.
    exit /b 1
)
:: =============================================
:: Leitura do nome a partir do arquivo info.json
for /f "tokens=2 delims=:," %%a in ('type info.json ^| findstr /C:"\"name\""') do (
    set "fileName=%%~a"
)

:: Remove espaços em branco ao redor do nome
set "fileName=%fileName: =%"
set "fileName=%fileName:~1,-1%"

:: Verifica se o nome foi obtido corretamente
if "%fileName%"=="" (
    echo Erro: Falha ao obter o nome do arquivo info.json.
    exit /b 1
)
set fullFileName=%fileName%.V%versao%

g++ -Wall -g3 -Wextra -static -static-libgcc -static-libstdc++ "rascunho/%fileName%.c" -o "builds/rascunho.exe"

if exist "builds/debug.exe" (
   del "builds/debug.exe"
)
g++ -Wall -g3 -Wextra -static -static-libgcc -static-libstdc++ %fileName%.c -o "builds/debug.exe"

g++ -Wall -g3 -Wextra -static -static-libgcc -static-libstdc++ %fileName%.c -o "builds/%fullFileName%.exe"

tar -a -c -f "zip/%fullFileName%.zip" *data *builds *rascunho *.pdf *.h *.c *.c functions.c *.cmd

msg * /v /w %fullFileName%.exe foi compilado!

start "RUN" "builds/%fullFileName%.exe"