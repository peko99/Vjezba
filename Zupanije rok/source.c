if (temp->naziv[0] > q->naziv[0]) {
		q->next = head->next;
		head->next = q;
		return head;
	}
	else if (temp->naziv[0] < q->naziv[0]) {
		Zupanija* previous = head;
		while (temp != NULL && temp->naziv[0] < q->naziv[0]) {
			temp = temp->next;
			previous = previous->next;
		}
		if (temp != NULL && temp->naziv[0] == q->naziv[0]) {
			if (strcmp(temp->naziv, q->naziv) == 0)
				return head;
			int i = 1;
			while (i < WORD_LEN) {
				if (temp->naziv[i] > q->naziv[i]) {
					previous->next = q;
					q->next = temp;
					return head;
				}
				else if (temp->naziv[i] < q->naziv[i]) {
					q->next = temp->next;
					temp->next = q;
					return head;
				}
				else
					i++;
			}
		}
		else {
			q->next = previous->next;
			previous->next = q;
			return head;
		}