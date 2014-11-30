#!/usr/bin/python

import tempfile
import time
import os
from Lockfile import (LockFile, ReleaseFile)


def UnitTestBase():
    '''
    UnitTest base case: lock/release
    '''
    try:
        tempFile = tempfile.mkstemp(
            prefix="testLockFile", dir=os.path.dirname(__file__))[1]
        assert(LockFile(tempFile) is True)
        time.sleep(1)
        assert(ReleaseFile(tempFile) is True)
    except Exception:
        print "<Fail> basic locking"
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
        assert(LockFile(tempFile, retry=10, timeout=0.2) is False)
        time.sleep(1)
        assert(ReleaseFile(tempFile) is True)
    except Exception:
        print "<Fail> cannot lock when it's been locked"
    os.unlink(tempFile)

if __name__ == "__main__":
    UnitTestBase()
    UnitTestCannotLock()
