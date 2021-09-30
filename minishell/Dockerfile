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

FROM ubuntu:latest as minishell

RUN apt-get -y update && apt-get -y upgrade 
RUN apt-get install -y bash vim gcc valgrind make libncurses5-dev libreadline-dev 
USER root
RUN mkdir -p /home/minishell/

CMD [ "bash" ]
