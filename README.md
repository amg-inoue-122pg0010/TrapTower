# TRAPTOWER

####■開発環境
visualstudio
####■使用ソフト
DXライブラリー
####■使用言語
C++

####■プロジェクト概要
プログラマー３人、プランナー2人、グラフィック5人のチームで制作しました。
3D空間でキャラクターを操作してトラップをよけつつゴールを目指すゲームです。
キャラクターの、ステージやトラップとの判定はベクトルを用いて自前で計算しています。

ProjectRoot  
│  
├─AppFrame  
│  │  Easing.cpp  
│  │  Easing.h  
│  │  Math.cpp  
│  │  Math.h  
│  │  Vector3D.cpp  
│  │  Vector3D.h  
│  │  
│  ├─source  
│     │  appframe.h  
│     │  
│     ├─Application  
│     │      ApplicationBase.cpp  
│     │      ApplicationBase.h  
│     │      UtilMacro.h  
│     │      WinMain.cpp  
│     │  
│     ├─CFile  
│     │      CFile.cpp  
│     │      CFile.h  
│     │      picojson.h  
│     │      utf8sjis.cpp  
│     │      utf8sjis.h  
│     │  
│     ├─Mode  
│     │      ModeBase.cpp  
│     │      ModeBase.h  
│     │      ModeServer.cpp  
│     │      ModeServer.h  
│     │  
│     └─ResourceServer  
│             ResourceServer.cpp  
│             ResourceServer.h  
│
├─Game  
│  ├─Game  
│      │  trap.json　（Excelから生成した、座標や種類等の情報を格納した.jsouファイル）  
│      │  Laser.json  
│      │  Player.json  
│      ├─source  
│      │      ApplicationMain.cpp  
│      │      ApplicationMain.h  
│      │      ApplicationGlobal.cpp  
│      │      ApplicationGlobal.h  
│      │      ObjectBase.cpp  
│      │      ObjectBase.h  
│      │      ModeAmgLogo.cpp  
│      │      ModeAmgLogo.h  
│      │      ModePause.cpp  
│      │      ModePause.h  
│      │      ModeStageSelect.cpp  
│      │      ModeStageSelect.h  
│      │      ModeTitle.cpp  
│      │      ModeTitle.h  
│      │      ModeGame.cpp  
│      │      ModeGame.h  
│      │      ModeGameOver.cpp  
│      │      ModeGameOver.h  
│      │      ModeMenu.cpp  
│      │      ModeMenu.h  
│      │      ModeGameClear.cpp  
│      │      ModeGameClear.h  
│      │      LaserCollisionBase.cpp  
│      │      LaserCollisionBase.h  
│      │      Gimmick.cpp  
│      │      Gimmick.h  
│      │      Player.cpp  
│      │      Player.h  
│      │  
│      └─res　（ゲームに使う画像やモデルなどを格納）  
│  
└─Dxlib（DX ライブラリ格納ディレクトリ）
