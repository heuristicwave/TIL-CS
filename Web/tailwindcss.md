# [tailwind css](https://tailwindcss.com/)

커스터마이징에 용이한 **utility-first** UI 프레임 워크

https://tailwindcss.com/docs

<br>



## utility-first CSS

class가 담당할 스타일을 미리 정의하고 필요한 class들을 조합해서 적용하는 식으로 사용

**Using Format**

```
.{property}{side}-{size}
```

<br>

### rem(root em)

rem : root font-size, 다른것에 영향 받지 않는 측정 단위

>  `em` : `%`, `px`와 같은 측정 단위(unit)



**em은 가장 가까운 font-size**

```css
.box {
    font-size:20px;
    .child {
        width: 2em;		/* 2em => 40px */
    }
}
```

<br>

## docs에 안나오는것

`border-section` border의 테두리가 사라짐