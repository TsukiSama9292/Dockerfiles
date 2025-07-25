### 編譯鏡像
```bash
docker build --no-cache -f judger-runner/python/Dockerfile --build-arg PYTHON_TAG=3.12-slim -t tsukisama9292/judger-runner:python-3.12 .
```
```bash
docker run -t -d tsukisama9292/judger-runner:python-3.12
```
```bash
docker build --no-cache -f judger-runner/node/Dockerfile --build-arg NODE_TAG=lts-bookworm-slim -t tsukisama9292/judger-runner:node-lts .
```
```bash
docker run -t -d tsukisama9292/judger-runner:node-lts
```
```bash
docker build --no-cache -f judger-runner/jdk/Dockerfile --build-arg JDK_TAG=17 -t tsukisama9292/judger-runner:jdk-17 .
```
```bash
docker run -t -d tsukisama9292/judger-runner:jdk-17
```
```bash
docker build --no-cache -f judger-runner/gcc/Dockerfile --build-arg GCC_TAG=15-bookworm -t tsukisama9292/judger-runner:gcc-15 .
```
```bash
docker run -t -d tsukisama9292/judger-runner:gcc-15
```