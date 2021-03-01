#!/bin/bash

export HOME=/home/"${USER}"
mkdir -p "${HOME}"
chown -R "${USER}" "${HOME}"
useradd --shell /bin/bash --system --create-home --uid "${UID}" --gid "${GID}" "${USER}" 2> /dev/null
exec gosu "${USER}" "$@"
