#!/bin/bash

find  ".git/modules" -iname "config" -exec sed -i '/worktree/d' {} \;
