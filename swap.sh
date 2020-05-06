#!/bin/bash
SWAP_DIR=$1
SWAP_SIZE=$2

echo "= Current Swap"
sudo swapon -s
echo "= Turning Off Swap"
sudo swapoff $SWAP_DIR
sudo rm $SWAP_DIR
echo "= Allocating "$SWAP_SIZE"GB Swap"
sudo fallocate -l $SWAP_SIZE\G $SWAP_DIR
echo "= Making Swap"
sudo mkswap $SWAP_DIR
echo "= Setting Permissions to Root Only"
sudo chmod 600 $SWAP_DIR
echo "= Turning On Swap"
sudo swapon $SWAP_DIR
echo "= Current Swap"
sudo swapon -s
echo "= Done!"