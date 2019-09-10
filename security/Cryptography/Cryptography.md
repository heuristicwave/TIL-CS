## Cryptography
<br>

### 스트림 암호화

고속으로 암호화 할 수 있고 경량적이어서 무선 환경이나 고속으로 동작하는 시스템에서 사용

예) LAN의 WEP에서 사용하는 RC4

1. 난수로 임의의 키를 선택해 키 스트림 결정
2. RC4는 메시지를 bit로 변환, 키스트림과 XOR하여 암호화 진행
   - XOR : 서로 다르면 1, 같으면 0

RC4에서 난수를 선택 할 때는 셔플링사용 256개의 바이트 중 하나를 선택



스트림 암호화는 키 스트림이 암호화 키가 되므로 어떻게 공유할지가 중요
<br>


**동기식 스트림 암호**

Gilbert Vernam - One Time Pad : 랜덤 번호를 생성해 송신자와 수신자가 랜덤 키를 교환
<br>
**비동기식**

키 스트림 생성 시, 이전의 평문 및 암호문에 종속적으로 생성
<br>




### 블록 암호화

사전에 공유한 암호키를 사용해 고정된 길이의 입력 블록을 고정된 길이의 출력으로 변환

1. Feistel 구조 : 역으로 수행하면 복호화 가능
2. SPN 구조 : 역으로 복호화 불가
<br>


#### Block Cipher

1. ECB (Electronic Code Book) Mode

   평문을 일정한 블록 단위로 나누어 순차적 암호화

   ex) DES는 블록을 64bit, AES는 128bit로 나눔

   평문을 각각의 단위로 나눌 때, 배수를 완성시키기 위해 padding를 추가하여 크기를 맞춤

   ![ECB](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d6/ECB_encryption.svg/601px-ECB_encryption.svg.png)

   한개의 블록이 해독되면 나머지 블록 또한 해독됨

   

2. CBC (Cipher Block Chaining) Mode

   ECB와 동일 방식으로 평문을 블록단위로 나눔

   최초 키의 생성 버퍼로 IV(Initialization Vector)가 사용되어 첫 번째 블록과 XOR 연산을 통해 암호화

   ![CBC](https://upload.wikimedia.org/wikipedia/commons/d/d3/Cbc_encryption.png)

   두 번째 블록부터는 첫 번째 블록의 암호화된 블록과 XOR을 진행

   **보안이 가장 강력한 암호화 모드**로 평가 받음, 암호화 및 복호화 시 병렬처리가 불가능

   

3. CFB (Cipher FeedBack) Mode

   EBC, CBC와 다르게 암호문과 평문의 길이가 같다.

   패딩을 추가 하지 않고, 스트림 방식으로 Bit 단위로 암호화를 수행.

   IV를 사용하고 암호화는 순차적으로 복호화는 병렬처리

   ![cFB](https://upload.wikimedia.org/wikipedia/commons/thumb/9/9d/CFB_encryption.svg/601px-CFB_encryption.svg.png)

   

4. OFB (Output FeedBack) Mode

   암호문과 평문의 길이가 동일

   패딩을 추가하지 않고 블록단위 스트림 암호화 방식

   암호화 함수는 키의 생성시에만 사용, 암, 복호화의 방식이 동일해 암호문을 암호화 하면 평문

   영상, 음성 데이터 신호에 주로 사용

   ![ofb](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f5/OFB_decryption.svg/601px-OFB_decryption.svg.png)

   

5. CTR (CounTeR) Mode

   평문블록과 키스트림을 XOR 연산해 암호문을 만든다. 암, 복호 방법이 동일

   키스트림 암호화 시 1씩 증가하는 카운터를 암호화한 Bit열, 병열처리 가능

   ![ctr](https://upload.wikimedia.org/wikipedia/commons/thumb/4/4d/CTR_encryption_2.svg/601px-CTR_encryption_2.svg.png)
<br>

#### 암호식과 운용 방식의 조합으로 얻을 수 있는 알고리즘의 가지수
AES128 / 192 / 256, SEED 128 / 256
위에서 소개한 운용 방식 5가지 => 5 * 5 = 25
<br>

#### RSA

- 대표적인 공개키 암호화(비대칭키 암호화) 방식

- 소인수 분해의 어려움을 기반으로 안정성 제공

- 암호화 및 디지털 서명 용도로 사용

1. 서로 다른 두 개의 소수 p와 q를 선정

2. (p-1)과 (q-1)에 각각 서로수인 정수 e를 준비

3. ed를 (p-1)(q-1)으로 나눈 나머지가 1이 되도록 하는 d를 찾음

4. N = pq를 계산하여 공개키 <N, e>와 개인키 <N, d>를 생성

5. 이후 p, q와 (p-1)(q-1) 값은 필요하지 않으므로 보안성을 위해 삭제
<br>

m은 N보다 작은 값으로 잘라낸 원문, c는 암호문 `c = m의e제곱 mod N`
<br>

암호문 c를 원문 m으로 복원하려면 비밀키 <N, d>로 연산 `m = c의d제곱 mod N`
<br>


https://wkdtjsgur100.github.io/RSA-algorithm/
<br>



기타


[RSA step by step](https://www.cryptool.org/en/cto-highlights/rsa-step-by-step)
[bigNum_Converter](https://www.mobilefish.com/services/big_number/big_number.php)
[RSA Calc](http://extranet.cryptomathic.com/rsacalc/index)
[비제네르](https://www.guballa.de/vigenere-solver)
