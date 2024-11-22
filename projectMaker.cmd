:: Criação das pastas, verificando se cada uma não existe
if not exist "builds" (
    mkdir "builds"
    "inicialization" >> builds/builds.config
)
if not exist "rascunho" (
    mkdir "rascunho"
    "inicialization" >> rascunho/rascunho.config
)
if not exist "data" (
    mkdir "data"
    "inicialization" >> data/data.config
)
if not exist "zip" (
    mkdir "zip"
    "inicialization" >> zip/zip.config
)

:: Criação do arquivo .gitignore com o conteúdo desejado, caso não exista
if not exist ".gitignore" (
    echo # EditorConfig is awesome: https://EditorConfig.org > .gitignore
    echo. >> .gitignore
    echo # top-most EditorConfig file >> .gitignore
    echo root = true >> .gitignore
    echo. >> .gitignore
    echo [*] >> .gitignore
    echo indent_style = space >> .gitignore
    echo indent_size = 4 >> .gitignore
    echo end_of_line = crlf >> .gitignore
    echo charset = utf-8 >> .gitignore
    echo trim_trailing_whitespace = false >> .gitignore
    echo insert_final_newline = false >> .gitignore
    echo. >> .gitignore
    echo # Arquivos padrão vscode e git >> .gitignore
    echo .vscode >> .gitignore
    echo .vscode/* >> .gitignore
    echo .github >> .gitignore
    echo. >> .gitignore
    echo # Ignorar arquivos de saída >> .gitignore
    echo output/ >> .gitignore
    echo output/* >> .gitignore
    echo output >> .gitignore
    echo. >> .gitignore
    echo # Ignorar arquivos JSON >> .gitignore
    echo *.json >> .gitignore
    echo. >> .gitignore
    echo # Ignorar arquivos BIN >> .gitignore
    echo *.bin >> .gitignore
)

:: Criação do arquivo info.json com os dados fornecidos, caso não exista
if not exist "info.json" (
    echo { > info.json
    echo     "name": "empity", >> info.json
    echo     "version": "0.0.1", >> info.json
    echo     "author": "LUIS DAS ARTIMANHAS & LUCAS GARCIA", >> info.json
    echo     "contact": "luisaugustodesouza785@gmail.com", >> info.json
    echo     "description": "empity", >> info.json
    echo     "license": "GNU General Public License v3.0" >> info.json
    echo } >> info.json
)

move "*.pdf" "data/"
move "*.txt" "data/"


:: Verifica o status dos arquivos
git status

:: Sincroniza com a nuvem antes de enviar
git pull

:: Adiciona todos os arquivos alterados, respeitando o .gitignore
git add .

:: Cria um commit com uma mensagem baseada no nome e versão do mod
git commit -m "Automated commit ProjectMaker"

:: Envia os arquivos para o repositório remoto na branch especificada
git push origin main

exit /b 0