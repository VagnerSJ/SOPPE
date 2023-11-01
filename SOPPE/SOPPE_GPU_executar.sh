#!/bin/bash
echo "Seu nome de usuário é:"
whoami
echo "Info de hora atual e tempo que o computador está ligado:"
uptime
echo "O script está executando do diretório:"
pwd

bash  /home/vagner/Documentos/tcc/MC-GPU_v12.3_RELEASE_2012-12-12/SOPPE.x /home/vagner/Documentos/tcc/MC-GPU_v12.3_RELEASE_2012-12-12/SOPPE_base_inputs.in | tee /home/vagner/Documentos/tcc/MC-GPU_v12.3_RELEASE_2012-12-12/SOPPE_GPU_base_inputs.out
