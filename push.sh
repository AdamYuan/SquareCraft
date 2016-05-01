#!/bin/bash
git reset --hard
git add ./*
git commit -m "$(date)"
git push origin master
