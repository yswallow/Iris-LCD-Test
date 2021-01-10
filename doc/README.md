# Iris LCD Test

## これなん

STM32ボードで2つの液晶に表示するサンプルです。


## ハードウェア

* [STM32F411CEUボード](https://github.com/WeActTC/MiniF4-STM32F4x1)

### 配線

| マイコン | 細長液晶 | 正方形液晶 |
|----|----|----|
| GND | P1,P3,P12,P22 | P1,P3,P12,P21(LED-),P22 |
| 3V3 | P18,P19 | P18,P19 |
| 5V |  | P20(LED+)(電流制限抵抗を入れること) |
| A0 | P4 | P4 |
| A1 | P5 | P5 |
| A2 | P6 | P6 |
| A3 | P7 | P7 |
| A4 | P8 | P8 |
| A5 | P9 | P9 |
| A6 | P10 | P10 |
| A7 | P11 | P11 |
| B0 | P2(RST) | P2(RST) |
| B1 | P13(RDX) |  |
| B2 | P14(WRX) |  |
| B3 | P15(CSX) |  |
| B4 | P16(DCX) |  |
| B5 |  | P15(CSX) |
| B6 |  | P16(DCX) |
| B7 |  | P14(WRX) |


他, 細長液晶のP20(LED+), P21(LED-)の間に6V程度の電源を電流制限抵抗を入れて繋ぐ


## 参考にしたコード

* [keshikan/Iris_LCD_sample](https://github.com/keshikan/Iris_LCD_sample) このリポジトリはこちらに正方形液晶用のコードを足したものになります。
* [lovyan03/LovyanGFX](https://github.com/lovyan03/LovyanGFX) 正方形液晶がILI9341であることはこちらのライブラリを使っていて判明しました。初期化コードを利用させていただいております。
* [htlabnet/inside_magimajopures](https://github.com/htlabnet/inside_magimajopures) 寿司の画像はこちらからコピーしました