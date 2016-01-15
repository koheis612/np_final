# ネットワークプログラミング最終課題
* Last Update: 2016/01/16(Sat)

## 概要
* TCPソケットによるじゃんけんプログラム
* ソースコード: http://github.com/koheis612/np_final/

## 機能
* クライアント側はサーバーに手(rock, paper, scissors)を送る。
* サーバ側は乱数によって手(rock, paper, scissors)を決め、勝敗を判定。結果をクライアント側に送信する。
    * 結果は win, lose, draw, bad のいずれか
* クライアント側で勝敗数を記録
* IPv4/IPv6 デュアルスタック
