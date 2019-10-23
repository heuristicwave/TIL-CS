## Linux Operating

[한글설정1](https://khe0616.tistory.com/37)

[한글설정2](https://m.blog.naver.com/talkativehacker/221284031607)



### FTP

[ftp_path](https://serverfault.com/questions/544850/create-new-vsftpd-user-and-lock-to-specify-home-login-directory)

안될때

```shell
/etc/passwd # 이곳에서 수정

==================or==================

sudo vi /etc/vsftpd.conf #수정.

# 수정내용

pam_service_name=vsftpd (수정 전)
pam_service_name=ftp (수정 gn)
```



active / passive - port

https://auctionpro.co.kr/?p=182

/etc/vsftpd.conf 이곳에다가 다음과 같은 명령 추가

```shell
listen_port=2121
ftp_data_port=2121
```

