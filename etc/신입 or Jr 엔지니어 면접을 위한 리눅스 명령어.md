# [신입 or Jr 엔지니어 면접을 위한 리눅스 명령어 top 10](https://youtu.be/u9RukvKZJZM)

<br>

## 1. Server 접속을 위한 SSH

🧐 학습 포인트 : SSH와 그 원리, 접근 제어 방법

- `etc/ssh/sshd_config` : ssh 관련 config 설정 ex) port
- `ssh {username}@{Server IP}` 형태로 접속하기

  ```shell
  ssh-add example.pem
  ```

<br>

## 2. IP 를 확인하는 `ifconfig` 과 `curl ifconfig.co`

<br>

## 3. 간단하게 http 테스트가 가능한 curl

🧐 학습 포인트 : GET, POST 지정 및 -v 옵션

- `-i` : 사이트의 Header와 바디 정보를 함께 가져오기 (Manifest Download)
- `-X` : 사용할 방식 메소드 선택하기 (`curl -X PUT -G {URL}`)
- `-G` : 전송할 사이트 url 및 ip 주소
- `-v` : SSL 정보 포함 (`curl -v https://www.google.com`)

<br>

## 4. 도메인 조회를 하는 nslookup

1. `/etc/hosts` 검색
2. `/etc/resolve.conf` 에서 DNS 서버 확인

<br>

## 5. 서버를 확인하는 telnet(nc), ping

🧐 학습 포인트 : TCP, UDP, ICMP 등 프로토콜 인지

<br>

## 6. 서버와 커넥션을 확인하는 netstat

🧐 학습 포인트 : netstat 명령어와 옵션 사용

- `netstat -Intpu`
- `netstat -au | grep {port}`

<br>

## 7. 프로세스를 확인하는 ps

🧐 학습 포인트 : ef vs aux

- `ps -ef | grep ""`
- `ps aux | grep ""`

<br>

## 8. 시스템정보를 확인하는 top, sar, free, df

🧐 학습 포인트 : `/proc/*` 경로에 관한 정보, user, nice, system, iowat 의미

<br>

## 9. 리눅스의 서비스를 관리하는 systemd

🧐 학습 포인트 : `service`, `sysctl` 등의 이해 여부 `init.d`, `upstart`

<br>

## 10. 리눅스 파일 권한을 관리하는 chmod, chown

<br>

## 그 외

🧐 학습 포인트

- 리눅스 부팅 프로세스 (/etc/profile, /etc/rc\*, cloud-init)
- fdisk, lvm, mkfs 등 파일시스템
- yum, apt 등 repo
- 커널 파리미터, 퍼포먼스 튜닝
