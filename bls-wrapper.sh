#!/bin/sh
# İlk gerçek kullanıcıyı bul ve dizinini hazırla
REAL_UID=$(awk -F: '$3 >= 1000 && $3 < 60000 {print $3; exit}' /etc/passwd)
REAL_USER=$(getent passwd $REAL_UID | cut -d: -f1)

if [ -n "$REAL_UID" ]; then
    RDIR="/run/user/$REAL_UID"
    [ ! -d "$RDIR" ] && mkdir -p "$RDIR" && chown "$REAL_USER:$REAL_USER" "$RDIR" && chmod 700 "$RDIR"
fi
exec /usr/bin/based-login