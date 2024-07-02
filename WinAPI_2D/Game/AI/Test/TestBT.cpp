#include "TestBT.h"

#include "TestNode.h"
#include "TestNode2.h"
#include "AI/Selector.h"
#include "AI/Sequence.h"

namespace LJG::AI
{
	Node* TestBT::SetupTree()
	{
		Node* root = new Selector("Do This!",
								  {new TestNode(), new TestNode2()}
		);
		return root;
	}
}
