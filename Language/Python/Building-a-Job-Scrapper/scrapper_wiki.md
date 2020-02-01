## 개발 순서
1. Get the page
2. Make Request
3. Extract the jobs



### 사용하는 라이브러리

[Requests Library](https://github.com/psf/requests) 
[BeautifulSoup](https://www.crummy.com/software/BeautifulSoup/bs4/doc/)



**필요 요소**
어떤부분의 정보를 크롤링 할지 태그 및 class 명

**부가물**(정교한 파싱)
[문자열 다루기_strip](https://shinygirl33.tistory.com/27)



## csv 결과물 스프레드시트에 import
1. upload on spreadsheet
2. check radio box
   - Replace spreadsheet / Comma / Yes





---

### 기억하고 싶은 것

**최종 리스트의 결과물을 알고 있을 때, 변수를 2개 선언하여 각자 따로 저장**
company[0], company[1] = > company, location
```python
company, location = html.find(
        "h3", {"class": "fc-black-700 fs-body1 mb4"}).find_all("span", recursive=False)
```



**정교하게 파싱하기**
결과물에 개행이나, 다른 문자 가 있을 때, 제거 방법

```python
company = company.get_text(strip=True).strip("-").strip("\r").strip("\n")
```