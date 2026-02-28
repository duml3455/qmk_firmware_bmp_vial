# HPY69

HPY69 は、`qmk_firmware_bmp_vial` 向けの 69 キー ANSI 配列キーボードです。`ble_micro_pro` をベースに、BLE Micro Pro と Vial で使えるように調整しています。

### 特徴

- 69 キーの ANSI 配列
- BLE Micro Pro と BMP Boost 対応
- Vial 対応キーマップ
- OLED には、BLE接続先などのステータスを表示

### 補足

- このキーボード定義は `keyboards/ble_micro_pro` を拡張して作成しています。
- デフォルトキーマップには BLE 制御用レイヤー、OLED 画像アセット、USB/BLE 出力状態を扱う独自ステータス処理が含まれています。
- デフォルトキーマップの左 Shift は `KC_LSFT` と `KC_INT5` を送るようにカスタマイズされています。

### ビルド

デフォルトキーマップのビルド:

```sh
make duml3455/hpy69:default:uf2
```

### デフォルトキーマップ

デフォルトキーマップには次のレイヤー群があります。

- 通常入力用のベースレイヤー
- ファンクションレイヤー
- BLE 制御レイヤー
- BLE ボンド削除レイヤー

デフォルトキーマップで使っている BLE 関連の独自キーコードは BMP 組み込みのキーコードを利用しているため、フラッシュ直後から Vial で再割り当てしなくても使用できます。

### ファイル構成

- `keyboards/duml3455/hpy69/`
    キーボード定義、プラットフォーム設定、リンカスクリプト
- `keyboards/duml3455/hpy69/keymaps/default/`
    デフォルトの Vial キーマップ、OLED 画像、BLE/OLED 状態管理、将来のポインティングデバイス用フック

### ステータス表示

デフォルトキーマップの OLED では次を表示します。

- USB モード
- BLE アイドル
- BLE 広告中の接続先
- BLE 接続中のスロット

OLED のタイムアウトと輝度は次で設定しています。

- `keyboards/duml3455/hpy69/keymaps/default/config.h`

### 今後の拡張

キーマップはすでにモジュール分割してあるため、トラックボール、マウスボタン、スクロール機能を比較的小さい変更で追加できます。

- `pointing.c/.h`
- `bmp_status.c/.h`
- `oled_status.c/.h`
