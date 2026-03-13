# GO HOTRELOAD

## What it is:
### This is a hotreload tool for GO. It automatically detects changes made to a specified project directory and reloads the server every time a change is detected 

## Usage:
### 1. Clone the repository:
'''bash
git clone https://github.com/Jeevaanandh/HotReload_GO
'''

### 2. Installation:
Change the directory to the cloned repository and install
'''bash
cd HotReload_GO
make install
'''

### 3. Run the hotreload command:
'''bash
hotreload --root <root_folder> --build "Build commands" --exec "run command"
'''

#### EG:
'''bash
hotreload --root /home/user/goBackend --build "go build -o server main.go" --exec "./server"
'''


## Note:
### This tool currently only runs on linux based Operating Systems. 