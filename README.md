# File System
#### 2018/09 - 2019/01  デザインパターンクラス
#### 期末プロジェクト

# 目標
#### クラスで紹介したパータンを活かしてファイルを管理するアプリケーションを作る

####  アプリケーションの機能
   * 目標フォルダの構造を表して、フォルダの内部ファイルの名前の隣りにファイルのサイズをつける。
   * ファイルの名前を変更。変更を保存。
   * ファイルの内容を表す。
   * ファイルの内容を変更。変更を保存。

# 機能
1. 目標フォルダの構造を表して、フォルダの内部ファイルの名前の隣りにファイルのサイズをつける。

![main page](/image/mainpage.png)


コマンドで目標フォルダを選んでから、アプリケーションで目標フォルダの構造を表す

下のコマンドをコマンドラインで入力する：

 bin/filesystem ｛目標フォルダ｝

例：
 ![command](/image/command.PNG)

Demo:
 [機能1](https://drive.google.com/file/d/1HJukDp3vXKt0IG05xKubMKE-XEyXnKua/view?usp=sharing)

2. ファイルの名前を変更。変更を保存。

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