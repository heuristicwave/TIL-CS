import pandas as pd
import requests
from tabulate import tabulate
from pandas import DataFrame


def getFinanceData(code):
    url = 'http://comp.fnguide.com/SVO2/ASP/SVD_Finance.asp?pGB=1&cID=&MenuYn=Y&ReportGB=&NewMenuID=103&stkGb=701&gicode=' + code
    res = requests.get(url)
    df = pd.read_html(res.text)
    temp_df = df[0]  # df[0] : year, df[1] : quarter, df[2] : ...
    # The last column value was recently announced quarter !!
    # EX) columns[:4] >> ['2017/12', '2018/12', '2019/12', '2020/06'], 5면 빠진 3분기 추가
    temp_df = temp_df[temp_df.columns[:5]]

    if temp_df.loc[0][0] == '매출액':
        temp_df = temp_df.loc[[0, 4, 15]]
        temp_df = temp_df.set_index(temp_df.columns[0])
    elif temp_df.loc[0][0] == '순이자손익':
        temp_df = temp_df.loc[[0, 9, 16]]
        temp_df = temp_df.set_index(temp_df.columns[0])
        temp_df = temp_df.rename(index={'순이자손익': '매출액'})
    elif temp_df.loc[0][0] == '영업수익계산에 참여한 계정 펼치기':
        temp_df = temp_df.loc[[0, 2, 9]]
        temp_df = temp_df.set_index(temp_df.columns[0])
        temp_df = temp_df.rename(index={'영업수익계산에 참여한 계정 펼치기': '매출액'})
    return temp_df

# 행열을 변환하고 연도별로 묶어 테이블을 만들고, 종목데이터를 순차적으로 덮음


def changeDataFrame(code, fs_df):
    for num, col in enumerate(fs_df.columns):
        temp_df = pd.DataFrame({code: fs_df[col]})
        temp_df = temp_df.T
        temp_df.columns = [[col]*len(fs_df), temp_df.columns]

        if num == 0:
            total_df = temp_df
        else:
            total_df = pd.merge(total_df, temp_df, how='outer',
                                left_index=True, right_index=True)
    return total_df


def convertStockCode(x):
    x = str(x)
    return 'A' + '0'*(6-len(x)) + x  # str로 캐스팅하면서 00 무시하는거 넣어줌


stock_code = pd.read_html(
    'http://kind.krx.co.kr/corpgeneral/corpList.do?method=download&searchType=13', header=0)[0]
stock_code = stock_code[['종목코드', '회사명']]
# DataFrame에서는 map대신 apply 사용
stock_code['종목코드'] = stock_code['종목코드'].apply(convertStockCode)

for num, code in enumerate(stock_code['종목코드']):
    if num is 5:
        break
    try:
        raw_Finance = getFinanceData(code)
        changed_fs_data = changeDataFrame(code, raw_Finance)
        if num == 0:
            total_fs = changed_fs_data
        else:
            total_fs = pd.concat([total_fs, changed_fs_data])
    except:
        pass

total_fs.to_excel('test.xlsx')
# print(total_fs)
