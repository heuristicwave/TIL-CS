## SQL

분명 DB에 기록된 정보인데 조회가 되지 않았다.

이유는 DB가 대소문자를 구분하기 때문이였다.

다음과 같이 **LIKE**를 사용하여 동일조건으로 맞춰주자

```sql
SELECT *
FROM 테이블명
WHERE UPPER(컬럼명) LIKE UPPER(검색명)
```



활용 예시

```javascript
let condition = [{ address: Address }, {symbol: ETH}];
let CA = await qrySelect(DB, "SELECT 컬럼명 FROM 테이블 WHERE LOWER(address) LIKE ? AND ?", condition);
```

