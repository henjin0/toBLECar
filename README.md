# toBLECar について

リモコンを紛失したりして動かなくなったラジコンカーを BLE 経由でブラウザから操作できるようにするためのプログラム群です。
ラジコンカーのモーターに任意のモータードライバ(DRV8835 など)へはんだ付けし、toBLECar.ino を M5Stack Atom lite に書き込むことで動作します。

M5Stack Atom lite への書き込み手順は下記リンクを参照する。

https://qiita.com/kmaepu/items/0c9400b2827e34e051fa

また、本リポジトリをローカルに直接ダウンロードして Chrome(バージョン 92.0.4515.131 にて動作確認)で toBLECar.html を開くことで、端末とラジコンカーを直接接続することができます。toBLECar.html の動作には JellyWare Inc.にて作成された Bluejelly.js と呼ばれるライブラリを使用しています。詳細は下記リンクを参照してください。

https://monomonotech.jp/kurage/webbluetooth/getting_started.html

# 組み立て方

under constructing.

# 使い方

ブラウザで toBLECar.html を開き、SCAN ボタンをクリックあるいはタップしてください。
すると BLE 端末の選択画面に移るため、"m5atom-rc"を選択してください。
その後、青い領域で前後方向、赤い方向で左右方向についてラジコンカーを操作することができます。

# LICENSE

Please see [LICENSE](LICENSE).
