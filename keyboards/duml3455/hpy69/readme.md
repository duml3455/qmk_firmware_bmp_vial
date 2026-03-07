# HPY69

HPY69 は、69 キー ANSI 配列キーボードです。

### 特徴

- 69キー、ANSI配列、一体型
- BLE Micro Pro(旧版) と BMP Boost(最新版) 両対応
- デフォルトでVialに対応
- OLEDには、BLE接続先などのステータスを表示

### 補足

- BLE Micro Pro (以下BMP)の詳細は、BMP開発者である sekigon-gonnoc さんが公開している [リポジトリ](https://github.com/sekigon-gonnoc/BLE-Micro-Pro.git) 並びに、 [公式ドキュメント](https://sekigon-gonnoc.github.io/BLE-Micro-Pro/#/) を参照してください。
- キーボード定義等は `keyboards/ble_micro_pro` を拡張して作成しています。
- duplexMatrix を使用しているので、Vial設定は必須です。
- デフォルトキーマップには BLE 制御用レイヤー、OLED 描画画像アセット、USB/BLE 出力状態を扱う独自ステータス処理が含まれています。

---
### ファイル構成

- `keyboards/duml3455/hpy69/`
    キーボード定義、プラットフォーム設定、リンカスクリプト
- `keyboards/duml3455/hpy69/keymaps/default/`
    デフォルトの Vial キーマップ、OLED 画像、BLE/OLED 状態管理など
- `keyboards/duml3455/hpy69/bmpconfig/`
    デフォルトの `config.json` と `config.bin` を格納しています。

---
### ビルド

BMPのファームウェアビルドには、BMP専用のリポジトリをクローンする必要があります。
sekigon-gonnoc さんが公開している、 `dev/ble-micro-pro` ブランチで環境構築を行ってからビルドを行ってください。

[vial-qmk](https://github.com/sekigon-gonnoc/vial-qmk.git)

デフォルトキーマップのビルド:

```sh
make duml3455/hpy69:default:uf2
```

### フラッシュ
DFUモードでBMPを接続し、コンパイルした `duml3455_hpy69_default.uf2` をフラッシュしてください。

`.uf2` のフラッシュ後には、 `keyboards/duml3455/hpy69/bmpconfig/config.bin` を書き込んでください。[BLE Micro Pro に設定ファイルを書き込む](https://sekigon-gonnoc.github.io/BLE-Micro-Pro/#/about_config_files?id=ble-micro-pro%e3%81%ab%e8%a8%ad%e5%ae%9a%e3%83%95%e3%82%a1%e3%82%a4%e3%83%ab%e3%82%92%e6%9b%b8%e3%81%8d%e8%be%bc%e3%82%80)

---
### デフォルトキーマップ

デフォルトキーマップは次のレイヤーを設定しています。

- 通常入力用のベースレイヤー
- ファンクションレイヤー
- BLE 制御レイヤー
- BLE ボンド削除レイヤー

sekigon-gonnoc さんが公開している [VIA custom UI for Vial](https://sekigon-gonnoc.github.io/via-custom-ui-for-vial/) あるいは [Vial Web](https://vial.rocks/) で変更できます。
VIA、Remapには対応していません。

なお、デフォルトキーマップにはすでに BLE 関連の独自キーコードを組み込んでいるため、フラッシュ直後から Vial で再割り当てしなくても使用できます。

---
### ステータス表示

デフォルトキーマップの OLED では次を表示します。

- USB 接続状態
- BLE アイドル状態
- BLE ホワイトリストなしアドバタイズ状態(BLEペアリング用)
- BLE ホワイトリスト登録済み機器へのアドバタイズ状態
- BLE ホワイトリスト登録済み機器への接続状態

デフォルトでは、すべて画像描画として表示しています。
描画データを編集する場合は [こちら](#oled描画バイナリ作成)

OLED のタイムアウトと輝度は下記で設定しています。

`keyboards/duml3455/hpy69/keymaps/default/config.h`

---
### OLED描画バイナリ作成
デフォルトでのOLEDは、すべてバイナリデータを描画する設定となっています。
描画するバイナリデータを変更したい場合は、 [image2cpp](https://javl.github.io/image2cpp/) が便利です。

1. Select image で 128x32 pixel 画像データを指定
2. 指定した画像データの色を反転する場合は、Background color: Black を指定
3. Preview を確認
4. Code output format: Plain bytes を指定
5. Draw mode: Horizontal - 1 bit per pixel を指定
6. Generate code をクリック
7. 生成されたテキストデータを、[images.c](keymaps/default/images.c) に貼付し、必要に応じて定義する

---
### 今後の拡張

キーマップはすでにモジュール分割してあるため、BLE 状態管理や OLED 表示の拡張を比較的小さい変更で追加できます。

- `bmp_status.c/.h`
- `oled_status.c/.h`
