## Linux Command

#### Add PATH

```shell
export PATH=$PATH:/root/.local/bin
```



#### Find

```shell
find / -name "aws"
```



#### AWS CLI

Windows에서는 export 대신 set명령어

```shell
LINUX / OSX
> export AWS_ACCESS_KEY_ID=ABCD123
> export AWS_SECRET_ACCESS_KEY=abcd123
> export AWS_SESSION_TOKEN=aaaaaaa
> export AWS_DEFAULT_REGION=us-east-1
```



### 하위폴더 권한 변경

```shell
# chmod
> chmod -R [8bit permission] [file name or folder name]

// test 하위 폴더와 파일들에 권한을 666(-rw-rw-rw-)로 변경
> chmod -R 666 test

# chown
> chown -R [owner name]:[group name] [filename or directory]
// test 하위 폴더와 파일들에 소유자를 alice 그룹을 bob로 설정합니다.

> chown -R alice:bob test
```



### 시간대 바꾸기

```shell
sudo rm -rf / etc/localtime
sudo ln -s /usr/share/zoneinfo/Asia/Seoul /etc/localtime
date
```

