#!/usr/bin/python
'''
Simple implementation for Linux lockfile
'''

import os
import time


def LockFile(target, retry=30, timeout=1):
    '''
    Use this method if you want to make sure only one process opens
    the "target" file. The "target" path should be a path to a file
    in an existing folder.

    Create a tmp folder in the same directory as target
    If the foler is created, we consider the target "locked"

    @return True: succeed; False: failed
    '''
    targetDir = os.path.dirname(os.path.realpath(target))
    if os.path.exists(targetDir) is False:
        return False
    lockFolder = os.path.join(targetDir, ".lock-" + os.path.basename(target))
    tryCnt = 0
    while tryCnt < retry:
        tryCnt += 1
        try:
            os.mkdir(lockFolder)
            return True
        except OSError:
            time.sleep(timeout)
    return False


def ReleaseFile(target):
    '''
    Release the target by trying to remove the tmp dir
    @return True: succeed; False: failed
    '''
    targetDir = os.path.dirname(os.path.realpath(target))
    if os.path.exists(targetDir) is False:
        return True
    lockFolder = os.path.join(targetDir, ".lock-" + os.path.basename(target))
    try:
        os.rmdir(lockFolder)
    except OSError:
        return False if os.path.exists(lockFolder) else True
    return True
