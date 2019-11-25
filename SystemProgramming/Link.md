## Link

```shell
# Hard Link
$ echo hello > hello_world
$ ln hello_world hello_hardlinked

$ stat hello_world # 링크 정보 확인
# 하드링크 링크갯수 2개로 늘어남, inode check
```

```shell
# Soft Link
$ ln -s hello_world hello_hardlinked

# ls -al
# ==> lrwxrwxrwx
```

