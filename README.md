# FreqMonitorAVR
商用電源周波数監視装置のAVRマイコンプログラムです

使用したAVRはAtmega328Pです。外部クロックを使用するようにヒューズを書き換え済み

インプットキャプチャを使用してゼロクロス信号を計時します。分解能は16MHz時におよそ0.002Hzです
またコード内でdoubleを使用していますがacr-gccではfloatもdoubleも32ビット幅になるため精度の差はありません
