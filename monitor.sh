#!/bin/bash

PROCESS_NAME="cub3D"

# Döngü yenileme hızı (saniye)
REFRESH_RATE=0.5

while true; do
    # Ekranı temizle
    clear
    
    # cub3D'nin PID'sini bul
    PID=$(pgrep -x "$PROCESS_NAME")

    if [ -z "$PID" ]; then
        echo "-----------------------------------------"
        echo " 🔍  $PROCESS_NAME bekleniyor..."
        echo "-----------------------------------------"
        echo " Lütfen oyunu diğer terminalden başlatın."
    else
        echo "-----------------------------------------"
        echo " 🟢  MONITORING: $PROCESS_NAME (PID: $PID)"
        echo "-----------------------------------------"
        
        # Linux ve MacOS uyumlu PS komutu
        # RSS: Resident Set Size (Programın kullandığı fiziksel RAM - KB cinsinden)
        # VSZ: Virtual Memory Size (Sanal bellek)
        
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            # Linux için çıktı
            ps -p "$PID" -o pid,%cpu,%mem,rss,cmd | head -n 1
            ps -p "$PID" -o pid,%cpu,%mem,rss,cmd | grep "$PROCESS_NAME"
        else
            # MacOS (42 Okulları) için çıktı
            ps -p "$PID" -o pid,%cpu,%mem,rss,comm
        fi

        echo "-----------------------------------------"
        echo " * RSS (Real Memory) sütununu takip et."
        echo " * Bu değer oyunda hareket ettikçe SABİT kalmalı."
        echo "-----------------------------------------"
        echo " Çıkmak için CTRL+C'ye bas."
    fi
    
    sleep $REFRESH_RATE
done
