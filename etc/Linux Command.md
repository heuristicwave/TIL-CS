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



### 폴더 권한

**chmod 7537**

| 주체        | 파일권한 | 내용                                                         |
| ----------- | -------- | ------------------------------------------------------------ |
| Owner(User) | r-s      | 소유자에 대한 setuid 권한은 4000, 읽기와 실행권한 5가 부여되어야함. |
| Group       | -ws      | 그룹에 대한 setuid 권한은 2000, 쓰기와 실행권한 3이 부여되어야 함. |
| Other user  | rwt      | "t"는 Sticky bit로 1000이 부여 "rwx"는 7이 부여되어야 한다.  |

4천+2천+1천 으로 특수권한이 7천, 파일에대한 권한은 5,3,7 => 7537 		참고 : (4,2,1)



### 시간대 바꾸기

```shell
sudo rm -rf / etc/localtime
sudo ln -s /usr/share/zoneinfo/Asia/Seoul /etc/localtime
date
```



#### [update  안될때](https://unix.stackexchange.com/questions/429729/apt-get-update-error-in-kali-linux-after-dist-upgrade)

