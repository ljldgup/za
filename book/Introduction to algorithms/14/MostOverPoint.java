package com.ljl;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class MostOverPoint {
	public static class Node {
		Node left;
		Node right;
		int v;
		int p;
		int max;
		int sum;

		public Node(int v, int p, int sum, int max) {
			this.v = v;
			this.p = p;
			this.max = max;
			this.sum = sum;
		}
	}

	public static Node dummy = new Node(-1, 0, 0, 0);

	public static Node buildTree(List<Point> pList, int left, int right) {
		if (left == right) return new Node(pList.get(left).value, pList.get(left).pValue, pList.get(left).pValue, 1);

		int mid = (left + right) / 2;


		Node leftNode = dummy, rightNode;
		if (mid > left) leftNode = buildTree(pList, left, mid - 1);
		rightNode = buildTree(pList, mid + 1, right);

		int rootSum = pList.get(mid).pValue + leftNode.sum + rightNode.sum;

		int rootMax = max(pList.get(mid).pValue + leftNode.sum, pList.get(mid).pValue + leftNode.sum + rightNode.sum, leftNode.max, rightNode.max);

		Node root = new Node(pList.get(mid).value, pList.get(mid).pValue, rootSum, rootMax);

		if (leftNode != dummy) root.left = leftNode;
		root.right = rightNode;

		return root;
	}

	private static int max(int... array) {
		int max = Integer.MIN_VALUE;
		for (int v : array) if (v > max) max = v;
		return max;
	}

	public static class Point {
		int value;
		//左端点1，右端点-1
		int pValue;

		public Point(int v, int pv) {
			this.value = v;
			this.pValue = pv;
		}
	}

	public static List<Point> getpList(int[][] intervals) {
		List<Point> pList = new ArrayList();
		for (int i = 0; i < intervals.length; i++) {
			pList.add(new Point(intervals[i][0], 1));
			pList.add(new Point(intervals[i][1], -1));
		}
		pList = pList.stream().sorted((x, y) -> Integer.compare(x.value, y.value) == 0 ?
				Integer.compare(-x.pValue, -y.pValue) : Integer.compare(x.value, y.value)).collect(Collectors.toList());
		return pList;
	}


	public static void main(String[] args) {
		int[][] intervals = {{1, 2}, {3, 5}, {4, 6}, {5, 7}, {8, 9}};
		List<Point> points = getpList(intervals);
		Node root = buildTree(points, 0, points.size() - 1);
		System.out.println(root.max);
	}
}