#!/bin/bash

groupadd \
    --gid "${GID}" \
    "${USER}"

useradd \
    --shell /bin/bash \
    --system \
    --create-home \
    --uid "${UID}" \
    --gid "${GID}" \
    "${USER}" \
    2> /dev/null

export HOME=/home/"${USER}"
mkdir -p "${HOME}"
chown -R "${USER}" "${HOME}"

exec gosu "${USER}" "$@"
