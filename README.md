# toBLECar について

リモコンを紛失したりして動かなくなったラジコンカーを BLE 経由でブラウザから操作できるようにするためのプログラム群です。
ラジコンカーのモーターに任意のモータードライバ(DRV8835 など)へはんだ付けし、toBLECar.ino を M5Stack Atom lite に書き込むことで動作します。

UIに関してはこちらからお試しできます。

https://henjin0.github.io/toBLECar/toBLECar.html


また、M5Stack Atom lite への書き込み手順は下記リンクを参照する。

https://qiita.com/kmaepu/items/0c9400b2827e34e051fa

また、本リポジトリをローカルに直接ダウンロードして Chrome(バージョン 92.0.4515.131 にて動作確認)で toBLECar.html を開くことで、端末とラジコンカーを直接接続することができます。toBLECar.html の動作には JellyWare Inc.にて作成された Bluejelly.js と呼ばれるライブラリを使用しています。詳細は下記リンクを参照してください。

https://monomonotech.jp/kurage/webbluetooth/getting_started.html

# 組み立て方(DCモーターで直接転舵するパターンのラジコンカー用)
DCモーターと戻りバネを組み合わせて左右への全開転舵を行うパターンにご使用ください。
こちらは[DRV8835](https://akizukidenshi.com/catalog/g/gK-09848/)などのＤＣモータドライバを使用します。
下記の対応に合わせて結線してください。

| ATOM | モータードライバ(IN) | モータードライバ(OUT) | アクチュエータ |
----|----|----|---- 
| G19  | AIN1  | AOUT1 | 前進・後進用モーターの前進側の端子 |
| G23  | AIN2  | AOUT2 | 前進・後進用モーターの後進側の端子 |
| G22  | BIN1  | BOUT1 | ステア操作用モーターの右折側の端子 |
| G33  | BIN2  | BOUT2 | ステア操作用モーターの左折側の端子 |

プログラムはtoBLECar.inoを使用してください。

# 組み立て方(サーボモーターで転舵するパターンのラジコンカー用)
サーボモーターで転舵するパターンにご使用ください。
こちらはM5Stack社の[ATOM Motion](https://www.switch-science.com/catalog/6993/)を使用します。
M1ポートに前進・後進用のモーターを接続し、S1ポートにステア操作用のサーボを接続してください。

| ATOM　Motion |  アクチュエータ |
----|---- 
| M1+  | 前進・後進用モーターの前進側の端子 |
| M1-  | 前進・後進用モーターの後進側の端子 |
| S1 | サーボモーターのSignal端子 |
| G | サーボモーターのGND端子 |
| V | サーボモーターのVcc端子 |

プログラムはtoBLECar_atom_motion.inoを使用してください。

# 使い方

ブラウザで toBLECar.html を開き、SCAN ボタンをクリックあるいはタップしてください。
すると BLE 端末の選択画面に移るため、"m5atom-rc"を選択してください。
その後、青い領域で前後方向、赤い方向で左右方向についてラジコンカーを操作することができます。

# LICENSE

Please see [LICENSE](LICENSE).
