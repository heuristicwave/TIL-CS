## Using Wireshark Hands On

udp.port == 1234

http.request && tcp



###### 와이어샤크 구성

툴바 -> 디스플레이필터 -> 패킷리스트 -> 패킷디테일 -> 패킷바이츠



nslookup naver.com



![ethernet header](https://i.stack.imgur.com/mJ5vI.gif)

Preamble : 777 감청부대

sos : 스스스돈돈돈스스스c

v : 돈돈돈스

돈돈돈스~ 돈돈돈스~ 돈돈돈스~ 일종의 Preamble

우리의 패킷에는 Preamble는 안보임



###### ipconfig /all 로 와이어 샤크 캐치 값과 비교하기

이더넷 데스티네이션 - 맨 앞 목적지의 gateway MAC Address(앞 6바이트)가 나옴

그다음 나의 맥 address 38-00-25-55-FC-16(앞 6바이트)

그다음 프로토콜 타입(앞 2바이트)

=> 14 BYTE



![IP HEADER](https://advancedinternettechnologies.files.wordpress.com/2012/01/ipv4-header.png?w=584)



##### packet.c					

```c
#include <stdint.h>
#include <stdio.h>

// consider data type size
static uint8_t packet[] = "Packet Detail -> COPY -> Escaped String";

void print_mac(uint8_t* mac) {
	// 없으면 공백 대신에 0넣고 자릿수 2자리
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void print_ip(uint8_t* ip) {
	printf("%d.%d.%d.%d\n", ip[0], ip[2], ip[2], ip[3]);
}

void print_port(uint8_t* port) {
	uint8_t a = port[0];
	uint8_t b = port[1];

    // printf("%d\n", port[0]*256 + port[1]):
    // uint16_t(port[0])로 타입 캐스팅 할 필요 없음
    // 내부적으로 연산시, eax레지스터로 연산하기 때문ㅍ 
	uint16_t port_hex = (a << 8) | b;
	printf("%d\n", port_hex);	// 16진수 c62f
}

int main() {
	printf("D-MAC : ");
	print_mac(&packet[0]);

	printf("S-MAC : ");
	print_mac(&packet[6]);	// 6 맥에 대한 offset

	printf("Protocol Type : %02x:%02x\n", packet[12], packet[13]);

	printf("S-IP : ");
	print_ip(&packet[14 + 12]);	// 26

	printf("D-IP : ");
	print_ip(&packet[14 + 16]); // 30 // 구조체로 만들어보자!
	// 14+20까지

	printf("S-Port : ");
	print_port(&packet[14 + 20]); // 34
	printf("D-Port : ");
	print_port(&packet[36]);
}
```



#### [Little & Big endian](https://m.blog.naver.com/PostView.nhn?blogId=wndrlf2003&logNo=70190031633&proxyReferer=https%3A%2F%2Fwww.google.com%2F)



n to h s(network byte order to host byte order short) : 16Bit 2bytes 바꾸기

h to n s(host byte order to network byte order short) : 16Bit 2bytes 바꾸기

n to h l(network to host long) : 32Bit 4bytes 바꾸기

h to n l(host to network long) : 32Bit 4bytes 바꾸기

n to h l l : 8bytes(표준 아님)



##### my_ntohs.c

```c
#include <stdint.h>
#include <stdio.h>

uint16_t my_ntohs(uint16_t n) { 
	return ((n & 0x00FF) << 8) | ((n & 0xFF00) >> 8);
	// return (n<<8) | (n>>8);
}

uint32_t my_ntohl(uint32_t m) {
	return ((m & 0xFF000000) >> 24) | ((m & 0x00FF0000) >> 8) |
		((m & 0x0000FF00) << 8) | ((m & 0x000000FF) << 24);
}

int main() {
	uint8_t packet[] = { 0x12, 0x34 };
	uint16_t* p = reinterpret_cast<uint16_t*>(packet);	// (uint16_t*)packet - gcc
	// uint16_t port = *p; 5000이 나옴

	uint16_t port = *p;
	port = my_ntohs(port);	// 바이트를 바꾸는 함수 3412 -> 1234

	printf("%x\n", port);

	{
		uint8_t	packet[] = { 0x12, 0x34, 0x56, 0x78 };

		uint32_t* p = reinterpret_cast<uint32_t*>(packet);
		uint32_t ip = *p;
		ip = my_ntohl(ip);

		printf("%x\n", ip);
	}
}

// “네트워크 바이트 정렬은 big endian 방식”
// intel cpu little endian 바뀌어서 들어감
// arm - big endian
```



[msdn](https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ntohs)에서 라이브러리 이름을 파악하여, 속성 링커 입력 종속성에다가 추가한다.

> 디버그한후, ctrl + art + D



#### 디스어셈블리로 확인하는 최적화

```assembly
;debug mode
0033197F  call        _ntohs@4 (03311DBh)

;release mode
01281077  push        dword ptr [packet]  
0128107A  call        dword ptr [__imp__ntohl@4 (01282040h)]

;my_ntohl (32bit)	bswap OPCODE존재
00D11073  mov         eax,dword ptr [packet]  
00D11076  bswap       eax  ; bswap은 32bit 레지스터

;my_ntohs (16bit)
00D11056  mov         ax,word ptr [packet]  
00D1105A  rol         ax,8  	; rol은 rotate
```