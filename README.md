# File System
#### 2018/09 - 2019/01  デザインパタークラス
#### 期末プロジェクト

# 目標
#### クラスで紹介したパータンを活かしてファイルを管理するアプリケーションを作る
* Composite パター：フォルダとファイルの複合構造。そうすれば、オブジェクトのタイプを判定必要がひくくなる。
* Iterator パター：フォルダオブジェクトの含めるファイルを直接使わせず、Iteratorを通してアクセスもる。フォルダオブジェクトのコンテナがわからなくてもアクセスできるようになる。
* Builder パター：Builderでフォルダとファイルの複合構造を構築する。主要プログラムがフォルダとファイルに対する依存がひくくなる。
* Visitor パター：フォルダとファイルの複合構造が既に固定された。複合構造を変えずに新しい機能を追加するため。
* Observer パター：フォルダとファイルが変更される
時、WxWidgetsで構築するUIが更新する必要がある。ObserverがUIとフォルダやファイのオブジェクトを分かれて。変更したら、UIプログラムを通知する。


####  アプリケーションの機能
   * 目標フォルダの構造を表して、フォルダの内部ファイルの名前の隣りにファイルのサイズをつける。
   * ファイルの名前を変更。変更を保存。
   * ファイルの内容を表す。
   * ファイルの内容を変更。変更を保存。

# 機能
1. **目標フォルダの構造を表して、フォルダの内部ファイルの名前の隣りにファイルのサイズをつける。**

![main page](/image/mainpage.png)


コマンドで目標フォルダを選んでから、アプリケーションで目標フォルダの構造を表す

下のコマンドをコマンドラインで入力する：

 bin/filesystem ｛目標フォルダ｝

例：
 ![command](/image/command.PNG)

Demo:
 [機能1](https://drive.google.com/file/d/1HJukDp3vXKt0IG05xKubMKE-XEyXnKua/view?usp=sharing)

2. **ファイルの名前を変更。変更を保存。**

左側ファイルやフォルダ名前のラベルをダブルクリックして、編集モードに入る。名前を変更してから、エンターを押すと、確認ダイアログが現れる。"yes"をクリックして変更を保存。さもないと、変更を放棄。この機能は本当にファイルやフォルダ名前を変更できる。

サイズのパーツは変更できない。

ダブルクリック：

 ![editTreeView](/image/editTreeView.png)

名前を変更してから、エンターを押す:

 ![Show dialog](/image/editTreeViewDialog.png)

サイズを変更すると：

 ![Edit size](/image/editSize.png)

サイズを変更してから、エンターを押すと、変化がない:

 ![Press `Enter` after editing size](/image/pressEnterAfterEditSize.png)

  Demo:
 [機能2](https://drive.google.com/file/d/1zJ2_eUUdu8mF-y0UMB2YE2a90CcmYhzz/view?usp=sharing)

3. **ファイルの内容を表す。**

左側の複合構造でラベルをクリックして、対応の内容が右側で現れる。クリックしたラベルのがフォルダやバイナリデータなど表示できない場合はディフォルトの文章を表す。

ディフォルト:

バイナリファイル＆リンク: "The file is not displayed in the editor because it uses an unsupported text encoding.".

フォルダ: do not show anything.

ラベルをクリックして、クリックしたファイルの中がテキスト場合：

 ![textContent page](/image/editViewShowTextfile.png)

ラベルをクリックして、ク表示できない場合：.

 ![binaryContent page](/image/editViewShowBinaryfileDefaultValue.png)

 Demo:
 [機能3](https://drive.google.com/file/d/1FhPhdp2hPRkcRN5gqjWMEMui4vtbp9JY/view?usp=sharing)

4. **ファイルの内容を変更。変更を保存**

  ファイルの内容を変更してから、"save"ボタンを押して変更を保存。もしくはctrl+sで変更を保存。セーブしたら、確認ダイアログが現れる。"yes"をクリックして変更を保存。さもないと、変更を放棄。この機能は本当にファイルやフォルダ内容を変更できる。

  内容を変更してから"save"ボタンを押すまたはctrl+sを入力すると：

  ![Show dialog](/image/editEditViewDialog.png)

  変更を保存:

  ![Save the change](/image/SaveEditView.png)

  フォイルの内容を変更するとフォイルのサイズも変化する。左側の情報が一緒に更新される。

 Demo:
 [機能4](https://drive.google.com/file/d/11sYX52X-NHpEnJR7U2_uvKJG5rqMBJXp/view?usp=sharing)

#

### プログラミング言語
C++
### ライブラリ
WxWidgets 3.0.5
### 環境
Linux or Ubuntu bash in win10.

# インストールと起動の手続き

Ubuntu bash in win10 の場合：

https://www.wxwidgets.org/downloads/ でwxWidgetsをダウンロードして、このプロジェクトの使うバージョンが3.0.5で、Windows ZIPをダウンロード。
解凍してから、bashを起動して、解凍のフォルダに入る。
例：

        cd /mnt/c/wxWidgets-3.0.4

コマンドを入力

        sudo apt-get update
        sudo apt-get install libwxgtk3.0-dev
        sudo apt-get install libgtk-3-dev build-essential checkinstall
        mkdir gtk-build
        cd gtk-build/
        ../configure --enable-unicode --enable-debug
        make
        sudo make install

コマンドを入力して、インストールが成功するかどうかを確認：

        wx-config --version

結果：

        3.0.5

VcXsrvをインストール：

https://sourceforge.net/projects/vcxsrv/  でVcXsrvをダウンロードして、インストールする。全部ディフォルトの設定でする。

XLaunchを起動。同じく全部ディフォルトの設定でする。

プロジェクトのフォルダで
        
        make
        export DISPLAY=:0
        bin/filesystem ｛目標フォルダ｝

"error while loading shared libraries: libwx_gtk3u_core-3.1.so.3: cannot open shared object file: No such file or directory"というメッセージが出る可能性がある。

        sudo apt-get install libwxgtk-webview3.0-gtk3-0v5 libwxgtk-media3.0-gtk3-0v5

そういうコメンドで解決。

Linux の場合：
https://www.kkaneko.jp/tools/ubuntu/wxwidgetslinux.html

