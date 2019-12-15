# Aria

[![GitHub Actions](https://img.shields.io/endpoint.svg?url=https://actions-badge.atrox.dev/MarkTuddenham/Aria/badge&label=build&logo=none)](https://actions-badge.atrox.dev/MarkTuddenham/Aria/goto)
[![Coverage Status](https://coveralls.io/repos/github/MarkTuddenham/Aria/badge.svg?branch=master)](https://coveralls.io/github/MarkTuddenham/Aria?branch=master)
![GitHub](https://img.shields.io/github/license/marktuddenham/Aria.svg)

![GitHub top language](https://img.shields.io/github/languages/top/marktuddenham/Aria.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/marktuddenham/Aria.svg)
![GitHub issues](https://img.shields.io/github/issues/marktuddenham/Aria.svg)
![GitHub closed issues](https://img.shields.io/github/issues-closed/marktuddenham/Aria.svg)

Chess with fog of war.

---

## Build Process

```bash
mkdir -p _build/

cmake -H. -B_build/
# or
cmake -H. -B_build/ -DCMAKE_BUILD_TYPE=Debug

# The above line may not work, if it doesn't then use:
pushd _build/ && cmake .. && popd

cmake --build _build/

# Run the tests
./bin/Tests

# Run the example
./bin/AriaExample
```

[Generate FEN positions](https://www.chessvideos.tv/chess-diagram-generator.php)

---

Copyright © 2019 Mark Tuddenham
