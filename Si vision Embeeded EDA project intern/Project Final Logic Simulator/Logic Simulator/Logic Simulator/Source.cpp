#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include <string>
#include <sstream>
#include<fstream>

class Node
{
	friend ostream& operator<<(ostream& os, const Node& other);

private:
	int NodeValue;
	string NodeName;

public:
	//Default Ctr
	Node() : NodeValue(0), NodeName("")
	{
		//rand() % 2 if even = 0 else 1 
		//	srand(time(NULL));    // initialize the random number generator	
		//	NodeName = 'A' + rand() % 26;;         // random char name
	}

	Node(string NodeName) :NodeName(NodeName), NodeValue(0)	//Non Default Ctr
	{
	}

	Node(int NodeValue, string NodeName) :NodeValue(NodeValue), NodeName(NodeName)	//Non Default Ctr
	{
	}
	~Node()
	{
	}
	void SetNodeValue(int NodeValuePassed)	//Setter node value
	{
		NodeValue = NodeValuePassed;
		//cout << "node is set" << endl;	//for debug
	}
	int GetNodeValue() const	//Getter node value
	{
		return NodeValue;
	}
	void SetNodeName(string NodeNamePassed)	//Setter node name
	{
		NodeName = NodeNamePassed;
	}
	string GetNodeName() const	//Getter node name
	{
		return NodeName;
	}


	/*virtual void AND_Gate() = 0;		//didn't used in my design
	virtual void OR_Gate() = 0;
	virtual void NAND_Gate() = 0;
	virtual void NOR_Gate() = 0;
	virtual void NOT_Gate() = 0;
	virtual void XNOR_Gate() = 0;
	virtual void XOR_Gate() = 0;*/

};

ostream& operator<<(ostream& os, const Node& other)
{
	os << other.NodeName << ": " << other.NodeValue << endl;
	return os;
}

class Gate
{

protected:

	Node* IN1;
	Node* IN2;
	Node* Out;


public:

	//Default Ctr
	Gate() : IN1(nullptr), IN2(nullptr), Out(nullptr)
	{
	}

	//Non Default Ctr
	Gate(Node* IN1, Node* IN2, Node* Out) : IN1(IN1), IN2(IN2), Out(Out)
	{
	}

	~Gate()
	{
	}

	void SetNode_IN1(Node* IN1_Passed)	//Setter node IN1
	{
		IN1 = IN1_Passed;
	}
	Node* GetNode_IN1() const	//Getter node IN1
	{
		return IN1;
	}

	void SetNode_IN2(Node* IN2_Passed)	//Setter node IN2
	{
		IN2 = IN2_Passed;
	}
	Node* GetNode_IN2() const	//Getter node IN2
	{
		return IN2;
	}

	void SetNode_Out(Node* Out_Passed)	//Setter node Out
	{
		Out = Out_Passed;
	}
	Node* GetNode_Out() const	//Getter node Out
	{
		return Out;
	}

	virtual void simulateGate() = 0;	//returns the logic value of the gate according to its type

};

//Create the gates which will be the child of the the base "Gate"
class AND : public Gate
{
public:
	AND() :Gate() {};
	~AND() {};

	void simulateGate()
	{
		if (IN1->GetNodeValue() == 1 && IN2->GetNodeValue() == 1)
		{
			Out->SetNodeValue(1);
		}
		else
		{
			Out->SetNodeValue(0);
		}
	}

};

class OR : public Gate
{
public:
	OR() :Gate() {};
	~OR() {};

	void simulateGate()
	{
		if (IN1->GetNodeValue() == 1 || IN2->GetNodeValue() == 1)
		{
			Out->SetNodeValue(1);
		}
		else
		{
			Out->SetNodeValue(0);
		}
	}

};

class NAND : public Gate
{
public:
	NAND() :Gate() {};
	~NAND() {};

	void simulateGate()
	{
		if (IN1->GetNodeValue() == 1 && IN2->GetNodeValue() == 1)
		{
			Out->SetNodeValue(0);
		}
		else
		{
			Out->SetNodeValue(1);
		}
	}

};

class NOR : public Gate
{
public:
	NOR() :Gate() {};
	~NOR() {};

	void simulateGate()
	{
		if (IN1->GetNodeValue() == 0 && IN2->GetNodeValue() == 0)
		{
			Out->SetNodeValue(1);
		}
		else
		{
			Out->SetNodeValue(0);
		}
	}

};

class XOR : public Gate
{
public:
	XOR() :Gate() {};
	~XOR() {};

	void simulateGate()
	{
		if (IN1->GetNodeValue() == IN2->GetNodeValue())
		{
			Out->SetNodeValue(0);
		}
		else
		{
			Out->SetNodeValue(1);
		}
	}

};

class XNOR : public Gate
{
public:
	XNOR() :Gate() {};
	~XNOR() {};

	void simulateGate()
	{
		if (IN1->GetNodeValue() == IN2->GetNodeValue())
		{
			Out->SetNodeValue(1);
		}
		else
		{
			Out->SetNodeValue(0);
		}
	}

};

class NOT : public Gate
{
public:
	NOT() :Gate() {};
	~NOT() {};

	void simulateGate()
	{
		if (IN1->GetNodeValue() == 0)
		{
			Out->SetNodeValue(1);
		}
		else
		{
			Out->SetNodeValue(0);
		}
	}

};

class Simulator
{

private:
	//Node* Arr_Nodes[1000];
	//Gate* Arr_Gates[1000];
	vector<Node*> nodes;
	vector<Gate*> gates;

	//int Node_size, Gate_size;
	int GATE_incremental;


public:
	Simulator()
	{
		GATE_incremental = 0;
	}
	~Simulator()
	{

	}

	void postGate(Gate* gate)
	{


		gates.push_back(gate);
		//Gate* Created_Gate = gate;
		//if no null return, so there exists a gate and will increment the number of gates
		//Gate_size++;
		//insert it to the array
		//Arr_Gates[Gate_size - 1] = Created_Gate;
		//return Arr_Gates[Gate_size - 1];
	}

	void postNode(Node* newNode)
	{

		nodes.push_back(newNode);
		//Arr_Nodes[Node_size] = newNode;
		//Node_size++;
		//return Arr_Nodes[Node_size - 1];
	}

	Node* FindNode(string node_Name)
	{
		Node* B = nullptr;

		
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i]->GetNodeName() == node_Name)
			{
				B = nodes[i];
			}
		}
		return B;

	}


	void startSimulate()
	{
		for (GATE_incremental; GATE_incremental < gates.size(); GATE_incremental++)
			gates[GATE_incremental]->simulateGate();
	}
};

class GateGenerator
{

private:

	vector<Node*> Vec_Nodes;
	vector<Gate*> Vec_Gates;

	int Node_number;	//number of nodes exist in vec
	int Gate_number;	//number of gates exist in vec

	Simulator* obj;


public:
	GateGenerator() : Node_number(0), Gate_number(0), obj(new Simulator)
	{

	}
	~GateGenerator()
	{
	}

	void parseInput()
	{
		string input_line;

		string Begin_str, gate, Node_To_BE_Set, Node_Set, Node_Value, Node_To_BE_Out, Node_Out;


		while (1)
		{

			if (cin.peek() != EOF)
			{

				getline(cin, input_line);
				stringstream ss(input_line);
				string word;
				if (input_line == "") {
					break;
				}
				//cout << "this is" << input_line;
				//while (ss >> word) {
				//	cout << word << endl;	//debug
				//}



				ss >> Begin_str;
				if (Begin_str == "AND" || Begin_str == "NAND" || Begin_str == "NOR" || Begin_str == "XOR" || Begin_str == "OR" || Begin_str == "XNOR")	//AND / OR / NAND / NOR / XOR / NOR 
				{

					gate = Begin_str;
					string nodeIN1;

					ss >> nodeIN1;
					if (!obj->FindNode(nodeIN1))
					{
						Node* n1 = createNode(nodeIN1);
						obj->postNode(n1);
					}

					string nodeIN2;
					ss >> nodeIN2;
					if (!obj->FindNode(nodeIN2))
					{
						Node* n2 = createNode(nodeIN2);
						obj->postNode(n2);
					}

					string nodeOUT;
					ss >> nodeOUT;
					if (!obj->FindNode(nodeOUT))
					{
						Node* n3 = createNode(nodeOUT);
						obj->postNode(n3);
					}

					Gate* gate_to_perform = createGate(gate);
					gate_to_perform->SetNode_IN1(obj->FindNode(nodeIN1));
					gate_to_perform->SetNode_IN2(obj->FindNode(nodeIN2));
					gate_to_perform->SetNode_Out(obj->FindNode(nodeOUT));
					obj->postGate(gate_to_perform);

					//cout << gate_to_perform->GetNode_IN1()->GetNodeValue() << endl;		//for debug

				}
				else if (Begin_str == "NOT") /// NOT
				{
					gate = Begin_str;
					string nodeIN1;

					ss >> nodeIN1;
					if (!obj->FindNode(nodeIN1))
					{
						Node* n1 = createNode(nodeIN1);
						obj->postNode(n1);
					}

					string nodeOUT;
					ss >> nodeOUT;
					if (!obj->FindNode(nodeOUT))
					{
						Node* n3 = createNode(nodeOUT);
						obj->postNode(n3);
					}

					Gate* gate_to_perform = createGate(gate);
					gate_to_perform->SetNode_IN1(obj->FindNode(nodeIN1));
					gate_to_perform->SetNode_Out(obj->FindNode(nodeOUT));
					obj->postGate(gate_to_perform);

				}
				else if (Begin_str == "SET")
				{
					Node_To_BE_Set = Begin_str;
					ss >> Node_Set >> Node_Value;

					if (!obj->FindNode(Node_Set))
					{
						Node* n1 = createNode(Node_Set);
						n1->SetNodeValue(stoi(Node_Value));
						obj->postNode(n1);
					}

					obj->FindNode(Node_Set)->SetNodeValue(stoi(Node_Value));

					//	cout << "Setting the node " << Node_Value <<" " << stoi(Node_Value)<< 
					//		Find_Node_Before_creation(Node_Set)->GetNodeValue() << endl;	//debug

				}
				else if (Begin_str == "SIM")
				{

					obj->startSimulate();

					//	cout << "Start Simulation" << endl;	//debug

				}
				else if (Begin_str == "OUT")
				{
					Node_To_BE_Out = Begin_str;
					ss >> Node_Out;
					if (Node_Out == "ALL")
					{
						for (int i = 0; i < Vec_Nodes.size(); i++)
						{
							//cout << Vec_Nodes[i]->GetNodeName() << ": " << Vec_Nodes[i]->GetNodeValue() << endl;
							cout << *Vec_Nodes[i];		//using overloading
						}

					}
					else
					{
						//cout << Find_Node_Before_creation(Node_Out)->GetNodeName() << ": " << Find_Node_Before_creation(Node_Out)->GetNodeValue() << endl;
						cout << *obj->FindNode(Node_Out);		//using overloading
					}
					//cout << "Print all nodes";	//debug
				}
				else
				{
					//cout << "Error" << endl;
					return;
				}

			}
			else
			{
				break;
			}

		}
	}



	Node* createNode(string nodeName)
	{
		auto node = new Node(nodeName);
		Vec_Nodes.push_back(node);
		Node_number++;

		//obj->postNode(node);

		return node;
	}
	Gate* createGate(string gateName)
	{
		Gate* gate = NULL;

		if (gateName == "AND")
			gate = new AND();

		else if (gateName == "OR")
			gate = new OR();

		else if (gateName == "NAND")
			gate = new NAND();

		else if (gateName == "NOR")
			gate = new NOR();

		else if (gateName == "XOR")
			gate = new XOR();

		else if (gateName == "XNOR")
			gate = new XNOR();

		else if (gateName == "NOT")
			gate = new NOT();

		else
			return NULL;



		Vec_Gates.push_back(gate);
		Gate_number++;

		//obj->postGate(gate);

		return gate;
	}


};


int main() {

	//Node* z = new Node(1, "A");
	//Node* h = new Node(1, "B");
	//Node* A = new Node(0, "C");
	//Gate* test2 = new AND;
	//test2->SetNode_IN1(z);
	//test2->SetNode_IN2(h);
	//test2->SetNode_Out(A);
	//test2->simulateGate();
	//cout << "C is" << test2->GetNode_Out()->GetNodeValue()<<endl;
	//cout << *z << endl;

	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	GateGenerator Logic_simulator;
	Logic_simulator.parseInput();

	//cout << "Start Logic";	//debug

	return 0;
}