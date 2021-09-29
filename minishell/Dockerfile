# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/25 03:02:08 by cbilbo            #+#    #+#              #
#    Updated: 2021/09/29 0 by cbilbo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine:3.12 as minishell

RUN apk update && apk upgrade \
	&& apk add bash vim gcc musl-dev lldb-dev readline-dev valgrind make

RUN mkdir -p /home/minishell/

ENV PATH=/home/minishell
ENV USER=minishell
ENV UID=12345
ENV GID=23456

RUN adduser "$USER"\
    --disabled-password \
    --gecos "" \
    --home /home/minishell \
    --uid "$UID" \
    "$USER"

CMD [ "bash" ]
