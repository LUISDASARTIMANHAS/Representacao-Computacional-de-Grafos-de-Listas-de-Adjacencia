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

:: Inicializa o repositório Git (se necessário)
if not exist ".git" (
    git init
    git remote add origin https://github.com/LUISDASARTIMANHAS/Representacao-Computacional-de-Grafos-de-Listas-de-Adjacencia.git
)

:: Verifica o status dos arquivos
git status

:: Adiciona todos os arquivos alterados, respeitando o .gitignore
git add .

:: Cria um commit com uma mensagem baseada no nome e versão do mod
git commit -m "Automated commit for %fullFileName%"

:: Envia os arquivos para o repositório remoto na branch especificada
git push origin main

exit /b 0