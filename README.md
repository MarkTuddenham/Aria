# DarkChess

[![GitHub Actions](https://img.shields.io/endpoint.svg?url=https://actions-badge.atrox.dev/MarkTuddenham/DarkChess/badge&label=build&logo=none)](https://actions-badge.atrox.dev/MarkTuddenham/DarkChess/goto)
[![Coverage Status](https://coveralls.io/repos/github/MarkTuddenham/DarkChess/badge.svg?branch=master)](https://coveralls.io/github/MarkTuddenham/DarkChess?branch=master)
![GitHub](https://img.shields.io/github/license/marktuddenham/DarkChess.svg)

![GitHub top language](https://img.shields.io/github/languages/top/marktuddenham/DarkChess.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/marktuddenham/DarkChess.svg)
![GitHub issues](https://img.shields.io/github/issues/marktuddenham/DarkChess.svg)
![GitHub closed issues](https://img.shields.io/github/issues-closed/marktuddenham/DarkChess.svg)

Chess with fog of war.

---

## Build Process

```bash
mkdir -p _build/
cmake -H. -B_build/
# The above line may not work, if it doesn't then use:
# pushd _build/ && cmake .. && popd

cmake --build _build/

# Run an example
./bin/DarkChessExample
```
