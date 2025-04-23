import pandas as pd

df = pd.read_csv(
    "https://www.taifex.com.tw/data_gov/taifex_open_data.asp?data_name=DailyForeignExchangeRates",
    encoding="cp950",
)