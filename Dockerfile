FROM gcc
WORKDIR .
CMD [ "/bin/bash" ]

RUN apt-get -y install \
    gcc \
    # ライブラリの追加