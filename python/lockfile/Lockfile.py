#!/usr/bin/python
'''
Simple implementation for Linux lockfile
'''

import os
import time


def LockFile(target, retry=30, timeout=1):
    '''
    Use this method if you want to make sure only one process opens
    the "target" file. The "target" file should exist.

    Create a tmp folder in the same directory as target
    If the foler is created, we consider the target "locked"

    @return True: succeed; False: failed
    '''
    targetDir = os.path.dirname(os.path.realpath(target))
    if os.path.exists(targetDir) is False:
        # See if we could use "/var/lock" folder..
        targetDir = "/var/lock"
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


def UnitTestBase():
    '''
    UnitTest base case: lock/release
    '''
    import tempfile
    try:
        tempFile = tempfile.mkstemp(
            prefix="testLockFile", dir=os.path.dirname(__file__))[1]
        assert(LockFile(tempFile) is True)
        time.sleep(1)
        assert(ReleaseFile(tempFile) is True)
    except Exception:
        pass
    os.unlink(tempFile)


def UnitTestCannotLock():
    '''
    UnitTest: cannot lock a file when it's been locked
    '''
    import tempfile
    try:
        tempFile = tempfile.mkstemp(
            prefix="testLockFile", dir=os.path.dirname(__file__))[1]
        assert(LockFile(tempFile) is True)
        time.sleep(1)
        # Try to lock again..it should return False
        assert(LockFile(tempFile, retry=10, timeout=0.2) is True)
        time.sleep(1)
        assert(ReleaseFile(tempFile) is True)
    except Exception:
        pass
    os.unlink(tempFile)

if __name__ == "__main__":
    UnitTestBase()
    UnitTestCannotLock()
