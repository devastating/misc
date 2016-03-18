"use strict";

/*
 * Definition for singly-linked list.
 *
 * @param
 * @return {ListNode}
 */
function ListNode(val) {
    this.val = val;
    this.next = null;
}

var heap = function() {
    // Containing lists
    this.lists = [];
    this.addElem = function(newList) {
        this.lists.push(newList);
        this.heapUp(this.lists.length - 1);
    }
    this.heapUp = function(elemIdx) {
        while (elemIdx > 0)
        {
            var topIdx = (elemIdx - 1) >> 1;
            if (this.lists[elemIdx].val < this.lists[topIdx].val)
            {
                var tmp = this.lists[elemIdx];
                this.lists[elemIdx] = this.lists[topIdx];
                this.lists[topIdx] = tmp;
                elemIdx = topIdx;
            }
            else
            {
                break;
            }
        }
    }
    this.removeList = function(elemIdx) {
        if (elemIdx >= this.lists.length)
        {
            throw "Remove out-of-range";
        }
        this.lists[elemIdx] = this.lists[this.lists.length - 1];
        this.lists.pop();
        if (this.lists.length > 0)
        {
            this.heapDown(elemIdx);
        }
    }
    this.heapDown = function(elemIdx) {
        var nextIdx = (elemIdx + 1) * 2 - 1;
        while (nextIdx < this.lists.length)
        {
            var swap = false;
            if (this.lists[elemIdx].val > this.lists[nextIdx].val)
            {
                swap = true;
            }
            if (nextIdx + 1 < this.lists.length)
            {
                if (swap === true)
                {
                    if (this.lists[nextIdx].val > this.lists[nextIdx + 1].val)
                    {
                        nextIdx += 1;
                    }
                }
                else
                {
                    if (this.lists[elemIdx].val > this.lists[nextIdx + 1].val)
                    {
                        swap = true
                        nextIdx += 1;
                    }
                }
            }
            if (swap === false)
            {
                break;
            }
            var tmp = this.lists[elemIdx];
            this.lists[elemIdx] = this.lists[nextIdx];
            this.lists[nextIdx] = tmp;
            elemIdx = nextIdx;
            nextIdx = (elemIdx + 1) * 2 - 1;
        }
    }
    this.empty = function() {
        return (this.lists.length == 0);
    }
    this.updateTop = function() {
        if (this.empty())
        {
            return NaN;
        }
        var ret = this.lists[0].val;
        this.lists[0] = this.lists[0].next;
        if (this.lists[0] === null)
        {
            this.removeList(0);
        }
        else
        {
            this.heapDown(0);
        }
        return ret;
    }
};

var mergeKLists = function(lists) {
    if (lists.length === 0)
    {
        return []
    }
    var mergeHeap = new heap();
    var i = 0;
    for (i = 0; i < lists.length; i++)        
    {
        if (lists[i] instanceof ListNode)
        {
            mergeHeap.addElem(lists[i]);
        }
    }
    var ret = null;
    var nodeIter = null;
    while (mergeHeap.empty() == false)
    {
        var topVal = mergeHeap.updateTop();
        var newNode = new ListNode(topVal);
        if (ret === null)
        {
            ret = newNode;
            nodeIter = newNode;
        }
        else
        {
            nodeIter.next = newNode;
            nodeIter = newNode;
        }
    }
    return ret === null? []: ret;
};

function generateList(elems)
{
    var i = 0;
    var ret = null;
    var prevNode = null;
    for (i = 0; i < elems.length; i++)
    {
        var newNode = new ListNode(elems[i]);
        if (ret === null)
        {
            ret = newNode;
            prevNode = newNode;
        }
        else
        {
            prevNode.next = newNode;
            prevNode = newNode;
        }
    }
    return ret;
}

function test3(elemArray) {
    var i = 0;
    var lists = [];
    for (i = 0; i < elemArray.length; i++)
    {
        var newList = generateList(elemArray[i]);
        lists.push(newList);
    }
    var mergedList = mergeKLists(lists);
    process.stdout.write("Merged result:\n");
    while (mergedList !== null)
    {
        process.stdout.write(mergedList.val.toString() + " ");
        mergedList = mergedList.next;
    }
    process.stdout.write("\n");
}

function test1() {
    // Create two lists
    var head1 = new ListNode(0);
    var head2 = new ListNode(1);
    var i = 0;
    var nodeIter = head1, nodeIter2 = head2;
    for (i = 0; i < 10; i++)
    {
        var nextNode = new ListNode(i * 2 + 2);
        var nextNode2 = new ListNode(i * 2 + 3);
        nodeIter.next = nextNode;
        nodeIter = nextNode;
        nodeIter2.next = nextNode2;
        nodeIter2 = nextNode2;
    }
    var mergedList = mergeKLists([head1, head2]);
    process.stdout.write("Merged result:\n");
    while (mergedList !== null)
    {
        process.stdout.write(mergedList.val.toString() + " ");
        mergedList = mergedList.next;
    }
    process.stdout.write("\n");

    mergedList = mergeKLists([head1]);
    process.stdout.write("Merged result2:\n");
    while (mergedList !== null)
    {
        process.stdout.write(mergedList.val.toString() + " ");
        mergedList = mergedList.next;
    }
    process.stdout.write("\n");
}

function test2() {
    // Create two lists
    var head1 = new ListNode(0);
    var head2 = new ListNode(1);
    var head3 = new ListNode(1);
    var i = 0;
    var nodeIter = head1, nodeIter2 = head2, nodeIter3 = head3;
    for (i = 0; i < 10; i++)
    {
        var nextNode = new ListNode(i * 2 + 2);
        nodeIter.next = nextNode;
        nodeIter = nextNode;
        if (i < 6)
        {
            var nextNode2 = new ListNode(i * 2 + 3);
            nodeIter2.next = nextNode2;
            nodeIter2 = nextNode2;
        }
        if (i < 8)
        {
            var nextNode2 = new ListNode(i * 2 + 1);
            nodeIter3.next = nextNode2;
            nodeIter3 = nextNode2;
        }
    }
    var mergedList = mergeKLists([head1, head2, head3]);
    process.stdout.write("Merged result:\n");
    while (mergedList !== null)
    {
        process.stdout.write(mergedList.val.toString() + " ");
        mergedList = mergedList.next;
    }
    process.stdout.write("\n");
}

var res = mergeKLists([]);
console.log(String(res));
res = mergeKLists([[]]);
console.log(res.toString());
test1();
test2();
test3([[-8,-7,-7,-5,1,1,3,4],[-2],[-10,-10,-7,0,1,3],[2]]);
