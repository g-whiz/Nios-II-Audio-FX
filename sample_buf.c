

typedef struct {
	int right;
	int left;
} Sample
  __attribute__ ((packed));

/* Convenience struct for accessing the components of the fifospace register. */
typedef struct {
	unsigned char read_r;
	unsigned char read_l;
	unsigned char write_r;
	unsigned char write_l;
} Fifospace 
  __attribute__ ((packed));

void write_sample(Sample *s);
void read_sample(Sample *s);

void get_fifospace(Fifospace *fspace);