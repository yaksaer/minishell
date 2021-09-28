# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/25 03:02:08 by cbilbo            #+#    #+#              #
#    Updated: 2021/09/28 15:20:26 by cbilbo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine:3.12 as minishell

RUN apk update && apk upgrade \
	&& apk add bash vim gcc musl-dev lldb-dev readline-dev valgrind make
RUN mkdir -p /minishell/
RUN chmod -R 777 /minishell/
WORKDIR /minishell/

CMD [ "bash" ]