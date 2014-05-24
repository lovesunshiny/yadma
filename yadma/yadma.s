
yadma.o:     file format elf32-i386


Disassembly of section .text:

00000000 <yadma_stats>:
	/* remove procfs files */
	unregister_proc_files();
}

static void yadma_stats(unsigned long __opaque)
{
       0:	55                   	push   %ebp
       1:	89 e5                	mov    %esp,%ebp
       3:	e8 fc ff ff ff       	call   4 <yadma_stats+0x4>
    struct pci_dev *pdev = (struct pci_dev *)__opaque;

    if(yadmaDriverState == YADMA_UNINITIALIZED)
        return;

}
       8:	5d                   	pop    %ebp
       9:	c3                   	ret    

0000000a <netlink_data_ready>:

static struct sock *nl_sk = NULL;
static int nl_pid = -1;

void netlink_data_ready (struct sk_buff *skb)
{
       a:	55                   	push   %ebp
       b:	89 e5                	mov    %esp,%ebp
       d:	56                   	push   %esi
       e:	53                   	push   %ebx
       f:	83 ec 0c             	sub    $0xc,%esp
      12:	e8 fc ff ff ff       	call   13 <netlink_data_ready+0x9>
	struct nlmsghdr *nlh = NULL;

	nlh = (struct nlmsghdr *)skb->data;
      17:	8b b0 a0 00 00 00    	mov    0xa0(%eax),%esi

static struct sock *nl_sk = NULL;
static int nl_pid = -1;

void netlink_data_ready (struct sk_buff *skb)
{
      1d:	89 c3                	mov    %eax,%ebx
	struct nlmsghdr *nlh = NULL;

	nlh = (struct nlmsghdr *)skb->data;
	log_verbose("%s Received netlink message payload: 0x%x.\n",
      1f:	8b 46 10             	mov    0x10(%esi),%eax
      22:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
      29:	00 
      2a:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
      31:	89 44 24 08          	mov    %eax,0x8(%esp)
      35:	e8 fc ff ff ff       	call   36 <netlink_data_ready+0x2c>
		   __FUNCTION__, *(int*)NLMSG_DATA(nlh));

	nl_pid = nlh->nlmsg_pid; /*pid of sending process */
      3a:	8b 46 0c             	mov    0xc(%esi),%eax
      3d:	a3 38 00 00 00       	mov    %eax,0x38
			break;
		}
		default:
			break;
	}
	kfree_skb(skb);
      42:	89 d8                	mov    %ebx,%eax
      44:	e8 fc ff ff ff       	call   45 <netlink_data_ready+0x3b>
	//Wake interrupt if time for process received data is too long
	//wake_up_interruptible(sk->sleep);

	/* A kernel thread is waiting for message coming down from user-space */
	// skb = skb_recv_datagram(nl_sk, 0, 0, &err);
}
      49:	83 c4 0c             	add    $0xc,%esp
      4c:	5b                   	pop    %ebx
      4d:	5e                   	pop    %esi
      4e:	5d                   	pop    %ebp
      4f:	c3                   	ret    

00000050 <yadma_demo>:

}


static void yadma_demo(unsigned long __opaque)
{
      50:	55                   	push   %ebp
      51:	89 e5                	mov    %esp,%ebp
      53:	e8 fc ff ff ff       	call   54 <yadma_demo+0x4>
	struct pci_dev *pdev = (struct pci_dev *)__opaque;

	if(yadmaDriverState == YADMA_UNINITIALIZED)
      58:	83 3d 78 00 00 00 00 	cmpl   $0x0,0x78
      5f:	74 19                	je     7a <yadma_demo+0x2a>
		return;

	/* set the timer again */
	demo_timer.expires=jiffies + HZ;
      61:	a1 00 00 00 00       	mov    0x0,%eax
      66:	05 fa 00 00 00       	add    $0xfa,%eax
      6b:	a3 08 00 00 00       	mov    %eax,0x8
	add_timer(&demo_timer);
      70:	b8 00 00 00 00       	mov    $0x0,%eax
      75:	e8 fc ff ff ff       	call   76 <yadma_demo+0x26>
}
      7a:	5d                   	pop    %ebp
      7b:	c3                   	ret    

0000007c <yadma_dev_ioctl>:
                          unsigned int cmd, unsigned long arg)
#else
static long yadma_dev_ioctl(struct file * filp,
                          unsigned int cmd, unsigned long arg)
#endif
{
      7c:	55                   	push   %ebp
      7d:	89 e5                	mov    %esp,%ebp
      7f:	57                   	push   %edi
      80:	56                   	push   %esi
      81:	53                   	push   %ebx
      82:	83 ec 10             	sub    $0x10,%esp
      85:	e8 fc ff ff ff       	call   86 <yadma_dev_ioctl+0xa>
    int retval=0;

	GainStru gain_tx1;

    if(yadmaDriverState != YADMA_INITIALIZED)
      8a:	83 3d 78 00 00 00 01 	cmpl   $0x1,0x78
                          unsigned int cmd, unsigned long arg)
#else
static long yadma_dev_ioctl(struct file * filp,
                          unsigned int cmd, unsigned long arg)
#endif
{
      91:	89 d3                	mov    %edx,%ebx
      93:	89 ce                	mov    %ecx,%esi
    int retval=0;

	GainStru gain_tx1;

    if(yadmaDriverState != YADMA_INITIALIZED)
      95:	74 11                	je     a8 <yadma_dev_ioctl+0x2c>
    {
        /* Should not come here */
        log_verbose("Driver not yet ready!\n");
      97:	c7 04 24 2c 00 00 00 	movl   $0x2c,(%esp)
      9e:	e8 fc ff ff ff       	call   9f <yadma_dev_ioctl+0x23>
      a3:	e9 b0 00 00 00       	jmp    158 <yadma_dev_ioctl+0xdc>
        return -1;
    }

    log_verbose(KERN_INFO "Run char dev ioctl with code %d.\n", cmd);
      a8:	89 54 24 04          	mov    %edx,0x4(%esp)
      ac:	c7 04 24 43 00 00 00 	movl   $0x43,(%esp)
      b3:	e8 fc ff ff ff       	call   b4 <yadma_dev_ioctl+0x38>

    /* Check cmd type and value */
    if(_IOC_TYPE(cmd) != YADMA_MAGIC) return -ENOTTY;
      b8:	0f b6 c7             	movzbl %bh,%eax
      bb:	83 f8 59             	cmp    $0x59,%eax
      be:	0f 85 99 00 00 00    	jne    15d <yadma_dev_ioctl+0xe1>
    if(_IOC_NR(cmd) > YADMA_MAX_CMD) return -ENOTTY;
      c4:	80 fb 02             	cmp    $0x2,%bl
      c7:	0f 87 90 00 00 00    	ja     15d <yadma_dev_ioctl+0xe1>

    /* Check read/write and corresponding argument */
    if(_IOC_DIR(cmd) & _IOC_READ)
      cd:	85 db                	test   %ebx,%ebx
      cf:	79 22                	jns    f3 <yadma_dev_ioctl+0x77>
        if(!access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd)))
      d1:	89 d8                	mov    %ebx,%eax

/* how to get the thread information struct from C */
static inline struct thread_info *current_thread_info(void)
{
	return (struct thread_info *)
		(current_stack_pointer & ~(THREAD_SIZE - 1));
      d3:	89 e1                	mov    %esp,%ecx
      d5:	c1 e8 10             	shr    $0x10,%eax
      d8:	81 e1 00 e0 ff ff    	and    $0xffffe000,%ecx
      de:	25 ff 3f 00 00       	and    $0x3fff,%eax
      e3:	89 f2                	mov    %esi,%edx
      e5:	01 c2                	add    %eax,%edx
      e7:	19 ff                	sbb    %edi,%edi
      e9:	39 51 18             	cmp    %edx,0x18(%ecx)
      ec:	83 df 00             	sbb    $0x0,%edi
      ef:	85 ff                	test   %edi,%edi
      f1:	75 71                	jne    164 <yadma_dev_ioctl+0xe8>
            return -EFAULT;
    if(_IOC_DIR(cmd) & _IOC_WRITE)
      f3:	f7 c3 00 00 00 40    	test   $0x40000000,%ebx
      f9:	74 22                	je     11d <yadma_dev_ioctl+0xa1>
        if(!access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd)))
      fb:	89 d8                	mov    %ebx,%eax
      fd:	89 e1                	mov    %esp,%ecx
      ff:	c1 e8 10             	shr    $0x10,%eax
     102:	81 e1 00 e0 ff ff    	and    $0xffffe000,%ecx
     108:	25 ff 3f 00 00       	and    $0x3fff,%eax
     10d:	89 f2                	mov    %esi,%edx
     10f:	01 c2                	add    %eax,%edx
     111:	19 ff                	sbb    %edi,%edi
     113:	39 51 18             	cmp    %edx,0x18(%ecx)
     116:	83 df 00             	sbb    $0x0,%edi
     119:	85 ff                	test   %edi,%edi
     11b:	75 47                	jne    164 <yadma_dev_ioctl+0xe8>
            return -EFAULT;

    /* Looks ok, let us continue */
    switch(cmd)
     11d:	81 fb 02 59 08 40    	cmp    $0x40085902,%ebx
     123:	75 23                	jne    148 <yadma_dev_ioctl+0xcc>
					  unsigned long n)
{
	int sz = __compiletime_object_size(to);

	if (likely(sz == -1 || sz >= n))
		n = _copy_from_user(to, from, n);
     125:	89 f2                	mov    %esi,%edx
     127:	b9 08 00 00 00       	mov    $0x8,%ecx
     12c:	8d 45 ec             	lea    -0x14(%ebp),%eax
     12f:	e8 fc ff ff ff       	call   130 <yadma_dev_ioctl+0xb4>
#else
static long yadma_dev_ioctl(struct file * filp,
                          unsigned int cmd, unsigned long arg)
#endif
{
    int retval=0;
     134:	31 d2                	xor    %edx,%edx
    /* Looks ok, let us continue */
    switch(cmd)
    {

    case IOCTL_SET_TX1_GAIN:
        if(copy_from_user(&gain_tx1, (GainStru *)arg, sizeof(GainStru)))
     136:	85 c0                	test   %eax,%eax
     138:	74 2f                	je     169 <yadma_dev_ioctl+0xed>
        {
            log_verbose("\ncopy_from_user failed\n");
     13a:	c7 04 24 68 00 00 00 	movl   $0x68,(%esp)
     141:	e8 fc ff ff ff       	call   142 <yadma_dev_ioctl+0xc6>
     146:	eb 1c                	jmp    164 <yadma_dev_ioctl+0xe8>
        }

		break;

    default:
        log_verbose("Invalid command %d\n", cmd);
     148:	89 5c 24 04          	mov    %ebx,0x4(%esp)
     14c:	c7 04 24 80 00 00 00 	movl   $0x80,(%esp)
     153:	e8 fc ff ff ff       	call   154 <yadma_dev_ioctl+0xd8>
        retval = -1;
     158:	83 ca ff             	or     $0xffffffff,%edx
        break;
     15b:	eb 0c                	jmp    169 <yadma_dev_ioctl+0xed>
    }

    log_verbose(KERN_INFO "Run char dev ioctl with code %d.\n", cmd);

    /* Check cmd type and value */
    if(_IOC_TYPE(cmd) != YADMA_MAGIC) return -ENOTTY;
     15d:	ba e7 ff ff ff       	mov    $0xffffffe7,%edx
     162:	eb 05                	jmp    169 <yadma_dev_ioctl+0xed>
    if(_IOC_NR(cmd) > YADMA_MAX_CMD) return -ENOTTY;

    /* Check read/write and corresponding argument */
    if(_IOC_DIR(cmd) & _IOC_READ)
        if(!access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd)))
            return -EFAULT;
     164:	ba f2 ff ff ff       	mov    $0xfffffff2,%edx
        retval = -1;
        break;
    }

    return retval;
}
     169:	83 c4 10             	add    $0x10,%esp
     16c:	89 d0                	mov    %edx,%eax
     16e:	5b                   	pop    %ebx
     16f:	5e                   	pop    %esi
     170:	5f                   	pop    %edi
     171:	5d                   	pop    %ebp
     172:	c3                   	ret    

00000173 <yadma_dev_release>:

    return 0;
}

static int yadma_dev_release(struct inode * in, struct file * filp)
{
     173:	55                   	push   %ebp
     174:	89 e5                	mov    %esp,%ebp
     176:	50                   	push   %eax
     177:	e8 fc ff ff ff       	call   178 <yadma_dev_release+0x5>
    if(!yadmaUserOpen)
     17c:	83 3d 7c 00 00 00 00 	cmpl   $0x0,0x7c
     183:	75 13                	jne    198 <yadma_dev_release+0x25>
    {
        /* Should not come here */
        log_verbose(KERN_INFO "Device not in use\n");
     185:	c7 04 24 54 04 00 00 	movl   $0x454,(%esp)
     18c:	e8 fc ff ff ff       	call   18d <yadma_dev_release+0x1a>
        return -EFAULT;
     191:	b8 f2 ff ff ff       	mov    $0xfffffff2,%eax
     196:	eb 28                	jmp    1c0 <yadma_dev_release+0x4d>
    }

    log_verbose(KERN_INFO "Char device release\n");
     198:	c7 04 24 6a 04 00 00 	movl   $0x46a,(%esp)
     19f:	e8 fc ff ff ff       	call   1a0 <yadma_dev_release+0x2d>
	raw_spin_lock(&lock->rlock);
}

static inline void spin_lock_bh(spinlock_t *lock)
{
	raw_spin_lock_bh(&lock->rlock);
     1a4:	b8 74 00 00 00       	mov    $0x74,%eax
     1a9:	e8 fc ff ff ff       	call   1aa <yadma_dev_release+0x37>
	raw_spin_unlock(&lock->rlock);
}

static inline void spin_unlock_bh(spinlock_t *lock)
{
	raw_spin_unlock_bh(&lock->rlock);
     1ae:	b8 74 00 00 00       	mov    $0x74,%eax
    spin_lock_bh(&DmaStatsLock);
    yadmaUserOpen-- ;
     1b3:	ff 0d 7c 00 00 00    	decl   0x7c
     1b9:	e8 fc ff ff ff       	call   1ba <yadma_dev_release+0x47>
    spin_unlock_bh(&DmaStatsLock);

    return 0;
     1be:	31 c0                	xor    %eax,%eax
}
     1c0:	c9                   	leave  
     1c1:	c3                   	ret    

000001c2 <yadma_dev_open>:
static DEFINE_SPINLOCK(DmaStatsLock);


/* Character device file operations */
static int yadma_dev_open(struct inode * in, struct file * filp)
{
     1c2:	55                   	push   %ebp
     1c3:	89 e5                	mov    %esp,%ebp
     1c5:	52                   	push   %edx
     1c6:	e8 fc ff ff ff       	call   1c7 <yadma_dev_open+0x5>
    if(yadmaDriverState != YADMA_INITIALIZED)
     1cb:	83 3d 78 00 00 00 01 	cmpl   $0x1,0x78
     1d2:	74 11                	je     1e5 <yadma_dev_open+0x23>
    {
        log_verbose(KERN_INFO "Driver not yet ready!\n");
     1d4:	c7 04 24 82 04 00 00 	movl   $0x482,(%esp)
     1db:	e8 fc ff ff ff       	call   1dc <yadma_dev_open+0x1a>
        return -1;
     1e0:	83 c8 ff             	or     $0xffffffff,%eax
     1e3:	eb 28                	jmp    20d <yadma_dev_open+0x4b>
    }

    log_verbose(KERN_INFO "Char device open\n");
     1e5:	c7 04 24 9c 04 00 00 	movl   $0x49c,(%esp)
     1ec:	e8 fc ff ff ff       	call   1ed <yadma_dev_open+0x2b>
	raw_spin_lock(&lock->rlock);
}

static inline void spin_lock_bh(spinlock_t *lock)
{
	raw_spin_lock_bh(&lock->rlock);
     1f1:	b8 74 00 00 00       	mov    $0x74,%eax
     1f6:	e8 fc ff ff ff       	call   1f7 <yadma_dev_open+0x35>
	raw_spin_unlock(&lock->rlock);
}

static inline void spin_unlock_bh(spinlock_t *lock)
{
	raw_spin_unlock_bh(&lock->rlock);
     1fb:	b8 74 00 00 00       	mov    $0x74,%eax
    spin_lock_bh(&DmaStatsLock);
    yadmaUserOpen++;                 /* To prevent more than one GUI */
     200:	ff 05 7c 00 00 00    	incl   0x7c
     206:	e8 fc ff ff ff       	call   207 <yadma_dev_open+0x45>
    spin_unlock_bh(&DmaStatsLock);

    return 0;
     20b:	31 c0                	xor    %eax,%eax
}
     20d:	c9                   	leave  
     20e:	c3                   	ret    

0000020f <netlink_init>:
	/* A kernel thread is waiting for message coming down from user-space */
	// skb = skb_recv_datagram(nl_sk, 0, 0, &err);
}

void netlink_init(void)
{
     20f:	55                   	push   %ebp
     210:	89 e5                	mov    %esp,%ebp
     212:	83 ec 0c             	sub    $0xc,%esp
     215:	e8 fc ff ff ff       	call   216 <netlink_init+0x7>
 	nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, 0, netlink_data_ready, NULL, THIS_MODULE);
     21a:	31 c9                	xor    %ecx,%ecx
     21c:	ba 1f 00 00 00       	mov    $0x1f,%edx
     221:	b8 00 00 00 00       	mov    $0x0,%eax
     226:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
     22d:	00 
     22e:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
     235:	00 
     236:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     23d:	e8 fc ff ff ff       	call   23e <netlink_init+0x2f>
    log_verbose(KERN_INFO "netlink initialized, sock = %d.\n", nl_sk);
     242:	89 44 24 04          	mov    %eax,0x4(%esp)
     246:	c7 04 24 88 05 00 00 	movl   $0x588,(%esp)
	// skb = skb_recv_datagram(nl_sk, 0, 0, &err);
}

void netlink_init(void)
{
 	nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, 0, netlink_data_ready, NULL, THIS_MODULE);
     24d:	a3 6c 00 00 00       	mov    %eax,0x6c
    log_verbose(KERN_INFO "netlink initialized, sock = %d.\n", nl_sk);
     252:	e8 fc ff ff ff       	call   253 <netlink_init+0x44>
}
     257:	c9                   	leave  
     258:	c3                   	ret    

00000259 <netlink_destroy>:

void netlink_destroy(void)
{
     259:	55                   	push   %ebp
     25a:	89 e5                	mov    %esp,%ebp
     25c:	83 ec 08             	sub    $0x8,%esp
     25f:	e8 fc ff ff ff       	call   260 <netlink_destroy+0x7>
    log_verbose(KERN_INFO "netlink destroyed, sock = %d.\n", nl_sk);
     264:	a1 6c 00 00 00       	mov    0x6c,%eax
     269:	c7 04 24 ac 05 00 00 	movl   $0x5ac,(%esp)
     270:	89 44 24 04          	mov    %eax,0x4(%esp)
     274:	e8 fc ff ff ff       	call   275 <netlink_destroy+0x1c>
	netlink_kernel_release(nl_sk);
     279:	a1 6c 00 00 00       	mov    0x6c,%eax
     27e:	e8 fc ff ff ff       	call   27f <netlink_destroy+0x26>
}
     283:	c9                   	leave  
     284:	c3                   	ret    

00000285 <netlink_send_to_userspace>:

/* Assumption: Only one process is allowed to exchange data
 * with this driver through netlink */
void netlink_send_to_userspace(KucMessage*kuc, bool multicast)
{
     285:	55                   	push   %ebp
     286:	89 e5                	mov    %esp,%ebp
     288:	57                   	push   %edi
     289:	56                   	push   %esi
     28a:	53                   	push   %ebx
     28b:	83 ec 10             	sub    $0x10,%esp
     28e:	e8 fc ff ff ff       	call   28f <netlink_send_to_userspace+0xa>
				   gfp_t priority, int fclone, int node);
extern struct sk_buff *build_skb(void *data, unsigned int frag_size);
static inline struct sk_buff *alloc_skb(unsigned int size,
					gfp_t priority)
{
	return __alloc_skb(size, priority, 0, NUMA_NO_NODE);
     293:	31 c9                	xor    %ecx,%ecx
     295:	89 c7                	mov    %eax,%edi
	struct sk_buff *skb_out = NULL;
	struct nlmsghdr *nlh = NULL;

	skb_out = alloc_skb(NLMSG_SPACE(kuc->len),GFP_KERNEL);
     297:	8b 40 10             	mov    0x10(%eax),%eax
}

/* Assumption: Only one process is allowed to exchange data
 * with this driver through netlink */
void netlink_send_to_userspace(KucMessage*kuc, bool multicast)
{
     29a:	89 d3                	mov    %edx,%ebx
     29c:	c7 04 24 ff ff ff ff 	movl   $0xffffffff,(%esp)
     2a3:	ba d0 00 00 00       	mov    $0xd0,%edx
	struct sk_buff *skb_out = NULL;
	struct nlmsghdr *nlh = NULL;

	skb_out = alloc_skb(NLMSG_SPACE(kuc->len),GFP_KERNEL);
     2a8:	83 c0 13             	add    $0x13,%eax
     2ab:	83 e0 fc             	and    $0xfffffffc,%eax
     2ae:	e8 fc ff ff ff       	call   2af <netlink_send_to_userspace+0x2a>
	nlh = (struct nlmsghdr *)skb_out->data;
     2b3:	8b b0 a0 00 00 00    	mov    0xa0(%eax),%esi
     2b9:	89 c2                	mov    %eax,%edx
	nlh->nlmsg_len = NLMSG_SPACE(kuc->len);
     2bb:	8b 47 10             	mov    0x10(%edi),%eax
	nlh->nlmsg_pid = 0;  /* from kernel */
     2be:	c7 46 0c 00 00 00 00 	movl   $0x0,0xc(%esi)
	struct sk_buff *skb_out = NULL;
	struct nlmsghdr *nlh = NULL;

	skb_out = alloc_skb(NLMSG_SPACE(kuc->len),GFP_KERNEL);
	nlh = (struct nlmsghdr *)skb_out->data;
	nlh->nlmsg_len = NLMSG_SPACE(kuc->len);
     2c5:	83 c0 13             	add    $0x13,%eax
     2c8:	83 e0 fc             	and    $0xfffffffc,%eax
     2cb:	89 06                	mov    %eax,(%esi)
	nlh->nlmsg_pid = 0;  /* from kernel */
	nlh->nlmsg_flags = 0;

	log_verbose("%s: send message: 0x%x.\n", __FUNCTION__, *(int*)NLMSG_DATA(nlh));
     2cd:	8b 46 10             	mov    0x10(%esi),%eax

	skb_out = alloc_skb(NLMSG_SPACE(kuc->len),GFP_KERNEL);
	nlh = (struct nlmsghdr *)skb_out->data;
	nlh->nlmsg_len = NLMSG_SPACE(kuc->len);
	nlh->nlmsg_pid = 0;  /* from kernel */
	nlh->nlmsg_flags = 0;
     2d0:	66 c7 46 06 00 00    	movw   $0x0,0x6(%esi)

	log_verbose("%s: send message: 0x%x.\n", __FUNCTION__, *(int*)NLMSG_DATA(nlh));
     2d6:	c7 44 24 04 14 00 00 	movl   $0x14,0x4(%esp)
     2dd:	00 
     2de:	c7 04 24 ce 05 00 00 	movl   $0x5ce,(%esp)
     2e5:	89 44 24 08          	mov    %eax,0x8(%esp)
     2e9:	89 55 f0             	mov    %edx,-0x10(%ebp)
     2ec:	e8 fc ff ff ff       	call   2ed <netlink_send_to_userspace+0x68>

	/* copy the specific structure's content */
	memcpy(NLMSG_DATA(nlh), kuc->data, kuc->len);
     2f1:	8b 4f 10             	mov    0x10(%edi),%ecx
     2f4:	8d 46 10             	lea    0x10(%esi),%eax
     2f7:	8d 77 18             	lea    0x18(%edi),%esi
     2fa:	89 c7                	mov    %eax,%edi
     2fc:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)

	if(multicast) {
     2fe:	84 db                	test   %bl,%bl
     300:	8b 55 f0             	mov    -0x10(%ebp),%edx
		NETLINK_CB(skb_out).pid = 0;  /* from kernel */
     303:	c7 42 24 00 00 00 00 	movl   $0x0,0x24(%edx)
	log_verbose("%s: send message: 0x%x.\n", __FUNCTION__, *(int*)NLMSG_DATA(nlh));

	/* copy the specific structure's content */
	memcpy(NLMSG_DATA(nlh), kuc->data, kuc->len);

	if(multicast) {
     30a:	74 22                	je     32e <netlink_send_to_userspace+0xa9>
		NETLINK_CB(skb_out).pid = 0;  /* from kernel */
		/* to mcast group 1<<0 */
		NETLINK_CB(skb_out).dst_group = 1;
		/*multicast the message to all listening processes*/
		netlink_broadcast(nl_sk, skb_out, 0, 1, GFP_KERNEL);
     30c:	a1 6c 00 00 00       	mov    0x6c,%eax
	memcpy(NLMSG_DATA(nlh), kuc->data, kuc->len);

	if(multicast) {
		NETLINK_CB(skb_out).pid = 0;  /* from kernel */
		/* to mcast group 1<<0 */
		NETLINK_CB(skb_out).dst_group = 1;
     311:	c7 42 28 01 00 00 00 	movl   $0x1,0x28(%edx)
		/*multicast the message to all listening processes*/
		netlink_broadcast(nl_sk, skb_out, 0, 1, GFP_KERNEL);
     318:	c7 44 24 04 d0 00 00 	movl   $0xd0,0x4(%esp)
     31f:	00 
     320:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
     327:	e8 fc ff ff ff       	call   328 <netlink_send_to_userspace+0xa3>
     32c:	eb 1e                	jmp    34c <netlink_send_to_userspace+0xc7>
	} else {
		NETLINK_CB(skb_out).pid = 0;	  /* from kernel */
		NETLINK_CB(skb_out).dst_group = 0;  /* unicast */
		netlink_unicast(nl_sk, skb_out, nl_pid, MSG_DONTWAIT);
     32e:	8b 0d 38 00 00 00    	mov    0x38,%ecx
     334:	a1 6c 00 00 00       	mov    0x6c,%eax
		NETLINK_CB(skb_out).dst_group = 1;
		/*multicast the message to all listening processes*/
		netlink_broadcast(nl_sk, skb_out, 0, 1, GFP_KERNEL);
	} else {
		NETLINK_CB(skb_out).pid = 0;	  /* from kernel */
		NETLINK_CB(skb_out).dst_group = 0;  /* unicast */
     339:	c7 42 28 00 00 00 00 	movl   $0x0,0x28(%edx)
		netlink_unicast(nl_sk, skb_out, nl_pid, MSG_DONTWAIT);
     340:	c7 04 24 40 00 00 00 	movl   $0x40,(%esp)
     347:	e8 fc ff ff ff       	call   348 <netlink_send_to_userspace+0xc3>
	/* BE CAREFUL: You're not allowed to free the skb after you've sent it.
	 * nlmsg_unicast() will take care of that.
	 */

	/* Nerver call: nlmsg_free(skb_out); */
}
     34c:	83 c4 10             	add    $0x10,%esp
     34f:	5b                   	pop    %ebx
     350:	5e                   	pop    %esi
     351:	5f                   	pop    %edi
     352:	5d                   	pop    %ebp
     353:	c3                   	ret    

00000354 <Acks>:
    struct pci_dev *pdev;

}

u32 Acks(u32 dirqval)
{
     354:	55                   	push   %ebp
     355:	89 e5                	mov    %esp,%ebp
     357:	83 ec 0c             	sub    $0xc,%esp
     35a:	e8 fc ff ff ff       	call   35b <Acks+0x7>
    u32 retval=0;


    log_verbose(KERN_INFO "Acking %x with %x\n", dirqval, retval);
     35f:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
     366:	00 
     367:	89 44 24 04          	mov    %eax,0x4(%esp)
     36b:	c7 04 24 c6 06 00 00 	movl   $0x6c6,(%esp)
     372:	e8 fc ff ff ff       	call   373 <Acks+0x1f>
    return retval;
}
     377:	31 c0                	xor    %eax,%eax
     379:	c9                   	leave  
     37a:	c3                   	ret    

0000037b <IntrCheck>:
/* This function serves to handle the initial interrupt, as well as to
 * check again on pending interrupts, from the BH. If this is not done,
 * interrupts can stall.
 */
int IntrCheck(struct pci_dev * dev)
{
     37b:	55                   	push   %ebp
     37c:	89 e5                	mov    %esp,%ebp
     37e:	53                   	push   %ebx
     37f:	83 ec 08             	sub    $0x8,%esp
     382:	e8 fc ff ff ff       	call   383 <IntrCheck+0x8>
     387:	89 c3                	mov    %eax,%ebx
 * driver-specific data.  They are really just a wrapper around
 * the generic device structure functions of these calls.
 */
static inline void *pci_get_drvdata(struct pci_dev *pdev)
{
	return dev_get_drvdata(&pdev->dev);
     389:	8d 40 60             	lea    0x60(%eax),%eax
     38c:	e8 fc ff ff ff       	call   38d <IntrCheck+0x12>
    int retval = 0;
    struct PrivateDataStru *lp;

    lp = pci_get_drvdata(dev);
    log_verbose(KERN_INFO "IntrCheck: device %x\n", (u32) dev);
     391:	89 5c 24 04          	mov    %ebx,0x4(%esp)
     395:	c7 04 24 dc 06 00 00 	movl   $0x6dc,(%esp)
     39c:	e8 fc ff ff ff       	call   39d <IntrCheck+0x22>

    return retval;
}
     3a1:	31 c0                	xor    %eax,%eax
     3a3:	5a                   	pop    %edx
     3a4:	59                   	pop    %ecx
     3a5:	5b                   	pop    %ebx
     3a6:	5d                   	pop    %ebp
     3a7:	c3                   	ret    

000003a8 <ProcWriteIrqInterval>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteIrqInterval(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     3a8:	55                   	push   %ebp
     3a9:	89 e5                	mov    %esp,%ebp
     3ab:	83 ec 08             	sub    $0x8,%esp
     3ae:	e8 fc ff ff ff       	call   3af <ProcWriteIrqInterval+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     3b3:	c7 44 24 04 b4 02 00 	movl   $0x2b4,0x4(%esp)
     3ba:	00 
     3bb:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     3c2:	e8 fc ff ff ff       	call   3c3 <ProcWriteIrqInterval+0x1b>
	return 0;
}
     3c7:	31 c0                	xor    %eax,%eax
     3c9:	c9                   	leave  
     3ca:	c3                   	ret    

000003cb <ProcWriteFPGAReset>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteFPGAReset(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     3cb:	55                   	push   %ebp
     3cc:	89 e5                	mov    %esp,%ebp
     3ce:	83 ec 08             	sub    $0x8,%esp
     3d1:	e8 fc ff ff ff       	call   3d2 <ProcWriteFPGAReset+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     3d6:	c7 44 24 04 cc 02 00 	movl   $0x2cc,0x4(%esp)
     3dd:	00 
     3de:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     3e5:	e8 fc ff ff ff       	call   3e6 <ProcWriteFPGAReset+0x1b>
	return 0;
}
     3ea:	31 c0                	xor    %eax,%eax
     3ec:	c9                   	leave  
     3ed:	c3                   	ret    

000003ee <ProcWriteSysTiming>:
	return 0;
}


static int ProcWriteSysTiming(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     3ee:	55                   	push   %ebp
     3ef:	89 e5                	mov    %esp,%ebp
     3f1:	83 ec 08             	sub    $0x8,%esp
     3f4:	e8 fc ff ff ff       	call   3f5 <ProcWriteSysTiming+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     3f9:	c7 44 24 04 e0 02 00 	movl   $0x2e0,0x4(%esp)
     400:	00 
     401:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     408:	e8 fc ff ff ff       	call   409 <ProcWriteSysTiming+0x1b>
	return 0;
}
     40d:	31 c0                	xor    %eax,%eax
     40f:	c9                   	leave  
     410:	c3                   	ret    

00000411 <ProcWriteRFStatech2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteRFStatech2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     411:	55                   	push   %ebp
     412:	89 e5                	mov    %esp,%ebp
     414:	83 ec 08             	sub    $0x8,%esp
     417:	e8 fc ff ff ff       	call   418 <ProcWriteRFStatech2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     41c:	c7 44 24 04 f4 02 00 	movl   $0x2f4,0x4(%esp)
     423:	00 
     424:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     42b:	e8 fc ff ff ff       	call   42c <ProcWriteRFStatech2+0x1b>
	return 0;
}
     430:	31 c0                	xor    %eax,%eax
     432:	c9                   	leave  
     433:	c3                   	ret    

00000434 <ProcWriteRFStatech1>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteRFStatech1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     434:	55                   	push   %ebp
     435:	89 e5                	mov    %esp,%ebp
     437:	83 ec 08             	sub    $0x8,%esp
     43a:	e8 fc ff ff ff       	call   43b <ProcWriteRFStatech1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     43f:	c7 44 24 04 08 03 00 	movl   $0x308,0x4(%esp)
     446:	00 
     447:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     44e:	e8 fc ff ff ff       	call   44f <ProcWriteRFStatech1+0x1b>
	return 0;
}
     453:	31 c0                	xor    %eax,%eax
     455:	c9                   	leave  
     456:	c3                   	ret    

00000457 <ProcWriteRSSIch2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteRSSIch2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     457:	55                   	push   %ebp
     458:	89 e5                	mov    %esp,%ebp
     45a:	83 ec 08             	sub    $0x8,%esp
     45d:	e8 fc ff ff ff       	call   45e <ProcWriteRSSIch2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     462:	c7 44 24 04 1c 03 00 	movl   $0x31c,0x4(%esp)
     469:	00 
     46a:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     471:	e8 fc ff ff ff       	call   472 <ProcWriteRSSIch2+0x1b>
	return 0;
}
     476:	31 c0                	xor    %eax,%eax
     478:	c9                   	leave  
     479:	c3                   	ret    

0000047a <ProcWriteRSSIch1>:
	return 0;
}


static int ProcWriteRSSIch1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     47a:	55                   	push   %ebp
     47b:	89 e5                	mov    %esp,%ebp
     47d:	83 ec 08             	sub    $0x8,%esp
     480:	e8 fc ff ff ff       	call   481 <ProcWriteRSSIch1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     485:	c7 44 24 04 30 03 00 	movl   $0x330,0x4(%esp)
     48c:	00 
     48d:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     494:	e8 fc ff ff ff       	call   495 <ProcWriteRSSIch1+0x1b>
	return 0;
}
     499:	31 c0                	xor    %eax,%eax
     49b:	c9                   	leave  
     49c:	c3                   	ret    

0000049d <ProcWriteRxGainch2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteRxGainch2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     49d:	55                   	push   %ebp
     49e:	89 e5                	mov    %esp,%ebp
     4a0:	83 ec 08             	sub    $0x8,%esp
     4a3:	e8 fc ff ff ff       	call   4a4 <ProcWriteRxGainch2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     4a8:	c7 44 24 04 44 03 00 	movl   $0x344,0x4(%esp)
     4af:	00 
     4b0:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     4b7:	e8 fc ff ff ff       	call   4b8 <ProcWriteRxGainch2+0x1b>
	return 0;
}
     4bc:	31 c0                	xor    %eax,%eax
     4be:	c9                   	leave  
     4bf:	c3                   	ret    

000004c0 <ProcWriteTxGainch2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteTxGainch2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     4c0:	55                   	push   %ebp
     4c1:	89 e5                	mov    %esp,%ebp
     4c3:	83 ec 08             	sub    $0x8,%esp
     4c6:	e8 fc ff ff ff       	call   4c7 <ProcWriteTxGainch2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     4cb:	c7 44 24 04 58 03 00 	movl   $0x358,0x4(%esp)
     4d2:	00 
     4d3:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     4da:	e8 fc ff ff ff       	call   4db <ProcWriteTxGainch2+0x1b>
	return 0;
}
     4df:	31 c0                	xor    %eax,%eax
     4e1:	c9                   	leave  
     4e2:	c3                   	ret    

000004e3 <ProcWriteRxGainch1>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteRxGainch1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     4e3:	55                   	push   %ebp
     4e4:	89 e5                	mov    %esp,%ebp
     4e6:	83 ec 08             	sub    $0x8,%esp
     4e9:	e8 fc ff ff ff       	call   4ea <ProcWriteRxGainch1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     4ee:	c7 44 24 04 6c 03 00 	movl   $0x36c,0x4(%esp)
     4f5:	00 
     4f6:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     4fd:	e8 fc ff ff ff       	call   4fe <ProcWriteRxGainch1+0x1b>
	return 0;
}
     502:	31 c0                	xor    %eax,%eax
     504:	c9                   	leave  
     505:	c3                   	ret    

00000506 <ProcWriteTxGainch1>:
	return 0;
}


static int ProcWriteTxGainch1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     506:	55                   	push   %ebp
     507:	89 e5                	mov    %esp,%ebp
     509:	83 ec 08             	sub    $0x8,%esp
     50c:	e8 fc ff ff ff       	call   50d <ProcWriteTxGainch1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     511:	c7 44 24 04 80 03 00 	movl   $0x380,0x4(%esp)
     518:	00 
     519:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     520:	e8 fc ff ff ff       	call   521 <ProcWriteTxGainch1+0x1b>
	return 0;
}
     525:	31 c0                	xor    %eax,%eax
     527:	c9                   	leave  
     528:	c3                   	ret    

00000529 <ProcWriteRxFreqch2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteRxFreqch2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     529:	55                   	push   %ebp
     52a:	89 e5                	mov    %esp,%ebp
     52c:	83 ec 08             	sub    $0x8,%esp
     52f:	e8 fc ff ff ff       	call   530 <ProcWriteRxFreqch2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     534:	c7 44 24 04 94 03 00 	movl   $0x394,0x4(%esp)
     53b:	00 
     53c:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     543:	e8 fc ff ff ff       	call   544 <ProcWriteRxFreqch2+0x1b>
	return 0;
}
     548:	31 c0                	xor    %eax,%eax
     54a:	c9                   	leave  
     54b:	c3                   	ret    

0000054c <ProcWriteTxFreqch2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteTxFreqch2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     54c:	55                   	push   %ebp
     54d:	89 e5                	mov    %esp,%ebp
     54f:	83 ec 08             	sub    $0x8,%esp
     552:	e8 fc ff ff ff       	call   553 <ProcWriteTxFreqch2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     557:	c7 44 24 04 a8 03 00 	movl   $0x3a8,0x4(%esp)
     55e:	00 
     55f:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     566:	e8 fc ff ff ff       	call   567 <ProcWriteTxFreqch2+0x1b>
	return 0;
}
     56b:	31 c0                	xor    %eax,%eax
     56d:	c9                   	leave  
     56e:	c3                   	ret    

0000056f <ProcWriteRxFreqch1>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteRxFreqch1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     56f:	55                   	push   %ebp
     570:	89 e5                	mov    %esp,%ebp
     572:	83 ec 08             	sub    $0x8,%esp
     575:	e8 fc ff ff ff       	call   576 <ProcWriteRxFreqch1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     57a:	c7 44 24 04 bc 03 00 	movl   $0x3bc,0x4(%esp)
     581:	00 
     582:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     589:	e8 fc ff ff ff       	call   58a <ProcWriteRxFreqch1+0x1b>
	return 0;
}
     58e:	31 c0                	xor    %eax,%eax
     590:	c9                   	leave  
     591:	c3                   	ret    

00000592 <ProcWriteTxFreqch1>:
	return 0;
}


static int ProcWriteTxFreqch1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     592:	55                   	push   %ebp
     593:	89 e5                	mov    %esp,%ebp
     595:	83 ec 08             	sub    $0x8,%esp
     598:	e8 fc ff ff ff       	call   599 <ProcWriteTxFreqch1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     59d:	c7 44 24 04 d0 03 00 	movl   $0x3d0,0x4(%esp)
     5a4:	00 
     5a5:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     5ac:	e8 fc ff ff ff       	call   5ad <ProcWriteTxFreqch1+0x1b>
	return 0;
}
     5b1:	31 c0                	xor    %eax,%eax
     5b3:	c9                   	leave  
     5b4:	c3                   	ret    

000005b5 <ProcWriteRxMemCh2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteRxMemCh2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     5b5:	55                   	push   %ebp
     5b6:	89 e5                	mov    %esp,%ebp
     5b8:	83 ec 08             	sub    $0x8,%esp
     5bb:	e8 fc ff ff ff       	call   5bc <ProcWriteRxMemCh2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     5c0:	c7 44 24 04 e4 03 00 	movl   $0x3e4,0x4(%esp)
     5c7:	00 
     5c8:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     5cf:	e8 fc ff ff ff       	call   5d0 <ProcWriteRxMemCh2+0x1b>
	return 0;
}
     5d4:	31 c0                	xor    %eax,%eax
     5d6:	c9                   	leave  
     5d7:	c3                   	ret    

000005d8 <ProcWriteRxMemCh1>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteRxMemCh1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     5d8:	55                   	push   %ebp
     5d9:	89 e5                	mov    %esp,%ebp
     5db:	83 ec 08             	sub    $0x8,%esp
     5de:	e8 fc ff ff ff       	call   5df <ProcWriteRxMemCh1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     5e3:	c7 44 24 04 f8 03 00 	movl   $0x3f8,0x4(%esp)
     5ea:	00 
     5eb:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     5f2:	e8 fc ff ff ff       	call   5f3 <ProcWriteRxMemCh1+0x1b>
	return 0;
}
     5f7:	31 c0                	xor    %eax,%eax
     5f9:	c9                   	leave  
     5fa:	c3                   	ret    

000005fb <ProcWriteTxMemCh2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcWriteTxMemCh2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     5fb:	55                   	push   %ebp
     5fc:	89 e5                	mov    %esp,%ebp
     5fe:	83 ec 08             	sub    $0x8,%esp
     601:	e8 fc ff ff ff       	call   602 <ProcWriteTxMemCh2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     606:	c7 44 24 04 0c 04 00 	movl   $0x40c,0x4(%esp)
     60d:	00 
     60e:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     615:	e8 fc ff ff ff       	call   616 <ProcWriteTxMemCh2+0x1b>
	return 0;
}
     61a:	31 c0                	xor    %eax,%eax
     61c:	c9                   	leave  
     61d:	c3                   	ret    

0000061e <ProcWriteTxMemCh1>:
	&ProcReadIrqInterval,

};

static int ProcWriteTxMemCh1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
     61e:	55                   	push   %ebp
     61f:	89 e5                	mov    %esp,%ebp
     621:	83 ec 08             	sub    $0x8,%esp
     624:	e8 fc ff ff ff       	call   625 <ProcWriteTxMemCh1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     629:	c7 44 24 04 20 04 00 	movl   $0x420,0x4(%esp)
     630:	00 
     631:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     638:	e8 fc ff ff ff       	call   639 <ProcWriteTxMemCh1+0x1b>
	return 0;
}
     63d:	31 c0                	xor    %eax,%eax
     63f:	c9                   	leave  
     640:	c3                   	ret    

00000641 <ProcReadIrqInterval>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadIrqInterval(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     641:	55                   	push   %ebp
     642:	89 e5                	mov    %esp,%ebp
     644:	83 ec 08             	sub    $0x8,%esp
     647:	e8 fc ff ff ff       	call   648 <ProcReadIrqInterval+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     64c:	c7 44 24 04 34 04 00 	movl   $0x434,0x4(%esp)
     653:	00 
     654:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     65b:	e8 fc ff ff ff       	call   65c <ProcReadIrqInterval+0x1b>
	return 0;
}
     660:	31 c0                	xor    %eax,%eax
     662:	c9                   	leave  
     663:	c3                   	ret    

00000664 <ProcReadFPGAReset>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadFPGAReset(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     664:	55                   	push   %ebp
     665:	89 e5                	mov    %esp,%ebp
     667:	83 ec 08             	sub    $0x8,%esp
     66a:	e8 fc ff ff ff       	call   66b <ProcReadFPGAReset+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     66f:	c7 44 24 04 48 04 00 	movl   $0x448,0x4(%esp)
     676:	00 
     677:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     67e:	e8 fc ff ff ff       	call   67f <ProcReadFPGAReset+0x1b>
	return 0;
}
     683:	31 c0                	xor    %eax,%eax
     685:	c9                   	leave  
     686:	c3                   	ret    

00000687 <ProcReadSysTiming>:
	return 0;
}


static int ProcReadSysTiming(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     687:	55                   	push   %ebp
     688:	89 e5                	mov    %esp,%ebp
     68a:	83 ec 08             	sub    $0x8,%esp
     68d:	e8 fc ff ff ff       	call   68e <ProcReadSysTiming+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     692:	c7 44 24 04 5c 04 00 	movl   $0x45c,0x4(%esp)
     699:	00 
     69a:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     6a1:	e8 fc ff ff ff       	call   6a2 <ProcReadSysTiming+0x1b>
	return 0;
}
     6a6:	31 c0                	xor    %eax,%eax
     6a8:	c9                   	leave  
     6a9:	c3                   	ret    

000006aa <ProcReadRFStatech2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadRFStatech2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     6aa:	55                   	push   %ebp
     6ab:	89 e5                	mov    %esp,%ebp
     6ad:	83 ec 08             	sub    $0x8,%esp
     6b0:	e8 fc ff ff ff       	call   6b1 <ProcReadRFStatech2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     6b5:	c7 44 24 04 70 04 00 	movl   $0x470,0x4(%esp)
     6bc:	00 
     6bd:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     6c4:	e8 fc ff ff ff       	call   6c5 <ProcReadRFStatech2+0x1b>
	return 0;
}
     6c9:	31 c0                	xor    %eax,%eax
     6cb:	c9                   	leave  
     6cc:	c3                   	ret    

000006cd <ProcReadRFStatech1>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadRFStatech1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     6cd:	55                   	push   %ebp
     6ce:	89 e5                	mov    %esp,%ebp
     6d0:	83 ec 08             	sub    $0x8,%esp
     6d3:	e8 fc ff ff ff       	call   6d4 <ProcReadRFStatech1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     6d8:	c7 44 24 04 84 04 00 	movl   $0x484,0x4(%esp)
     6df:	00 
     6e0:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     6e7:	e8 fc ff ff ff       	call   6e8 <ProcReadRFStatech1+0x1b>
	return 0;
}
     6ec:	31 c0                	xor    %eax,%eax
     6ee:	c9                   	leave  
     6ef:	c3                   	ret    

000006f0 <ProcReadRSSIch2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadRSSIch2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     6f0:	55                   	push   %ebp
     6f1:	89 e5                	mov    %esp,%ebp
     6f3:	83 ec 08             	sub    $0x8,%esp
     6f6:	e8 fc ff ff ff       	call   6f7 <ProcReadRSSIch2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     6fb:	c7 44 24 04 98 04 00 	movl   $0x498,0x4(%esp)
     702:	00 
     703:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     70a:	e8 fc ff ff ff       	call   70b <ProcReadRSSIch2+0x1b>
	return 0;
}
     70f:	31 c0                	xor    %eax,%eax
     711:	c9                   	leave  
     712:	c3                   	ret    

00000713 <ProcReadRSSIch1>:
	return 0;
}


static int ProcReadRSSIch1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     713:	55                   	push   %ebp
     714:	89 e5                	mov    %esp,%ebp
     716:	83 ec 08             	sub    $0x8,%esp
     719:	e8 fc ff ff ff       	call   71a <ProcReadRSSIch1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     71e:	c7 44 24 04 a8 04 00 	movl   $0x4a8,0x4(%esp)
     725:	00 
     726:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     72d:	e8 fc ff ff ff       	call   72e <ProcReadRSSIch1+0x1b>
	return 0;
}
     732:	31 c0                	xor    %eax,%eax
     734:	c9                   	leave  
     735:	c3                   	ret    

00000736 <ProcReadRxGainch2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadRxGainch2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     736:	55                   	push   %ebp
     737:	89 e5                	mov    %esp,%ebp
     739:	83 ec 08             	sub    $0x8,%esp
     73c:	e8 fc ff ff ff       	call   73d <ProcReadRxGainch2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     741:	c7 44 24 04 b8 04 00 	movl   $0x4b8,0x4(%esp)
     748:	00 
     749:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     750:	e8 fc ff ff ff       	call   751 <ProcReadRxGainch2+0x1b>
	return 0;
}
     755:	31 c0                	xor    %eax,%eax
     757:	c9                   	leave  
     758:	c3                   	ret    

00000759 <ProcReadTxGainch2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadTxGainch2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     759:	55                   	push   %ebp
     75a:	89 e5                	mov    %esp,%ebp
     75c:	83 ec 08             	sub    $0x8,%esp
     75f:	e8 fc ff ff ff       	call   760 <ProcReadTxGainch2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     764:	c7 44 24 04 cc 04 00 	movl   $0x4cc,0x4(%esp)
     76b:	00 
     76c:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     773:	e8 fc ff ff ff       	call   774 <ProcReadTxGainch2+0x1b>
	return 0;
}
     778:	31 c0                	xor    %eax,%eax
     77a:	c9                   	leave  
     77b:	c3                   	ret    

0000077c <ProcReadRxGainch1>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadRxGainch1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     77c:	55                   	push   %ebp
     77d:	89 e5                	mov    %esp,%ebp
     77f:	83 ec 08             	sub    $0x8,%esp
     782:	e8 fc ff ff ff       	call   783 <ProcReadRxGainch1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     787:	c7 44 24 04 e0 04 00 	movl   $0x4e0,0x4(%esp)
     78e:	00 
     78f:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     796:	e8 fc ff ff ff       	call   797 <ProcReadRxGainch1+0x1b>
	return 0;
}
     79b:	31 c0                	xor    %eax,%eax
     79d:	c9                   	leave  
     79e:	c3                   	ret    

0000079f <ProcReadTxGainch1>:
	return 0;
}


static int ProcReadTxGainch1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     79f:	55                   	push   %ebp
     7a0:	89 e5                	mov    %esp,%ebp
     7a2:	83 ec 08             	sub    $0x8,%esp
     7a5:	e8 fc ff ff ff       	call   7a6 <ProcReadTxGainch1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     7aa:	c7 44 24 04 f4 04 00 	movl   $0x4f4,0x4(%esp)
     7b1:	00 
     7b2:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     7b9:	e8 fc ff ff ff       	call   7ba <ProcReadTxGainch1+0x1b>
	return 0;
}
     7be:	31 c0                	xor    %eax,%eax
     7c0:	c9                   	leave  
     7c1:	c3                   	ret    

000007c2 <ProcReadRxFreqch2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadRxFreqch2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     7c2:	55                   	push   %ebp
     7c3:	89 e5                	mov    %esp,%ebp
     7c5:	83 ec 08             	sub    $0x8,%esp
     7c8:	e8 fc ff ff ff       	call   7c9 <ProcReadRxFreqch2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     7cd:	c7 44 24 04 08 05 00 	movl   $0x508,0x4(%esp)
     7d4:	00 
     7d5:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     7dc:	e8 fc ff ff ff       	call   7dd <ProcReadRxFreqch2+0x1b>
	return 0;
}
     7e1:	31 c0                	xor    %eax,%eax
     7e3:	c9                   	leave  
     7e4:	c3                   	ret    

000007e5 <ProcReadTxFreqch2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadTxFreqch2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     7e5:	55                   	push   %ebp
     7e6:	89 e5                	mov    %esp,%ebp
     7e8:	83 ec 08             	sub    $0x8,%esp
     7eb:	e8 fc ff ff ff       	call   7ec <ProcReadTxFreqch2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     7f0:	c7 44 24 04 1c 05 00 	movl   $0x51c,0x4(%esp)
     7f7:	00 
     7f8:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     7ff:	e8 fc ff ff ff       	call   800 <ProcReadTxFreqch2+0x1b>
	return 0;
}
     804:	31 c0                	xor    %eax,%eax
     806:	c9                   	leave  
     807:	c3                   	ret    

00000808 <ProcReadRxFreqch1>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadRxFreqch1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     808:	55                   	push   %ebp
     809:	89 e5                	mov    %esp,%ebp
     80b:	83 ec 08             	sub    $0x8,%esp
     80e:	e8 fc ff ff ff       	call   80f <ProcReadRxFreqch1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     813:	c7 44 24 04 30 05 00 	movl   $0x530,0x4(%esp)
     81a:	00 
     81b:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     822:	e8 fc ff ff ff       	call   823 <ProcReadRxFreqch1+0x1b>
	return 0;
}
     827:	31 c0                	xor    %eax,%eax
     829:	c9                   	leave  
     82a:	c3                   	ret    

0000082b <ProcReadTxFreqch1>:
	return 0;
}


static int ProcReadTxFreqch1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     82b:	55                   	push   %ebp
     82c:	89 e5                	mov    %esp,%ebp
     82e:	83 ec 08             	sub    $0x8,%esp
     831:	e8 fc ff ff ff       	call   832 <ProcReadTxFreqch1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     836:	c7 44 24 04 44 05 00 	movl   $0x544,0x4(%esp)
     83d:	00 
     83e:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     845:	e8 fc ff ff ff       	call   846 <ProcReadTxFreqch1+0x1b>
	return 0;
}
     84a:	31 c0                	xor    %eax,%eax
     84c:	c9                   	leave  
     84d:	c3                   	ret    

0000084e <ProcReadRxMemCh2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadRxMemCh2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     84e:	55                   	push   %ebp
     84f:	89 e5                	mov    %esp,%ebp
     851:	83 ec 08             	sub    $0x8,%esp
     854:	e8 fc ff ff ff       	call   855 <ProcReadRxMemCh2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     859:	c7 44 24 04 58 05 00 	movl   $0x558,0x4(%esp)
     860:	00 
     861:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     868:	e8 fc ff ff ff       	call   869 <ProcReadRxMemCh2+0x1b>
	return 0;
}
     86d:	31 c0                	xor    %eax,%eax
     86f:	c9                   	leave  
     870:	c3                   	ret    

00000871 <ProcReadRxMemCh1>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadRxMemCh1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     871:	55                   	push   %ebp
     872:	89 e5                	mov    %esp,%ebp
     874:	83 ec 08             	sub    $0x8,%esp
     877:	e8 fc ff ff ff       	call   878 <ProcReadRxMemCh1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     87c:	c7 44 24 04 6c 05 00 	movl   $0x56c,0x4(%esp)
     883:	00 
     884:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     88b:	e8 fc ff ff ff       	call   88c <ProcReadRxMemCh1+0x1b>
	return 0;
}
     890:	31 c0                	xor    %eax,%eax
     892:	c9                   	leave  
     893:	c3                   	ret    

00000894 <ProcReadTxMemCh2>:
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
	return 0;
}

static int ProcReadTxMemCh2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     894:	55                   	push   %ebp
     895:	89 e5                	mov    %esp,%ebp
     897:	83 ec 08             	sub    $0x8,%esp
     89a:	e8 fc ff ff ff       	call   89b <ProcReadTxMemCh2+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     89f:	c7 44 24 04 80 05 00 	movl   $0x580,0x4(%esp)
     8a6:	00 
     8a7:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     8ae:	e8 fc ff ff ff       	call   8af <ProcReadTxMemCh2+0x1b>
	return 0;
}
     8b3:	31 c0                	xor    %eax,%eax
     8b5:	c9                   	leave  
     8b6:	c3                   	ret    

000008b7 <ProcReadTxMemCh1>:

#endif


static int ProcReadTxMemCh1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
     8b7:	55                   	push   %ebp
     8b8:	89 e5                	mov    %esp,%ebp
     8ba:	83 ec 08             	sub    $0x8,%esp
     8bd:	e8 fc ff ff ff       	call   8be <ProcReadTxMemCh1+0x7>
	log_verbose(KERN_INFO "%s handle procfs read/write.\n",__FUNCTION__);
     8c2:	c7 44 24 04 94 05 00 	movl   $0x594,0x4(%esp)
     8c9:	00 
     8ca:	c7 04 24 f5 06 00 00 	movl   $0x6f5,(%esp)
     8d1:	e8 fc ff ff ff       	call   8d2 <ProcReadTxMemCh1+0x1b>
	return 0;
}
     8d6:	31 c0                	xor    %eax,%eax
     8d8:	c9                   	leave  
     8d9:	c3                   	ret    

000008da <rx_ch2_buffer_mmap>:
	return err;
}


static int rx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
     8da:	55                   	push   %ebp
     8db:	89 e5                	mov    %esp,%ebp
     8dd:	56                   	push   %esi
     8de:	53                   	push   %ebx
     8df:	83 ec 0c             	sub    $0xc,%esp
     8e2:	e8 fc ff ff ff       	call   8e3 <rx_ch2_buffer_mmap+0x9>
	int err;
	printk(KERN_INFO "rx_ch2_buffer mmap\n" );
     8e7:	c7 04 24 16 07 00 00 	movl   $0x716,(%esp)
	return err;
}


static int rx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
     8ee:	89 d6                	mov    %edx,%esi
	int err;
	printk(KERN_INFO "rx_ch2_buffer mmap\n" );
     8f0:	e8 fc ff ff ff       	call   8f1 <rx_ch2_buffer_mmap+0x17>
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
     8f5:	a1 00 00 00 00       	mov    0x0,%eax

static int rx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "rx_ch2_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
     8fa:	8b 4e 4c             	mov    0x4c(%esi),%ecx
	err = remap_pfn_range( vma,
     8fd:	8b 56 18             	mov    0x18(%esi),%edx
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
     900:	8b 40 30             	mov    0x30(%eax),%eax

static int rx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "rx_ch2_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
     903:	c1 e1 0c             	shl    $0xc,%ecx
	err = remap_pfn_range( vma,
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
     906:	89 cb                	mov    %ecx,%ebx
     908:	c1 fb 1f             	sar    $0x1f,%ebx
     90b:	03 48 08             	add    0x8(%eax),%ecx
     90e:	13 58 0c             	adc    0xc(%eax),%ebx
static int rx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "rx_ch2_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
     911:	8b 46 14             	mov    0x14(%esi),%eax
     914:	89 54 24 08          	mov    %edx,0x8(%esp)
     918:	8b 56 04             	mov    0x4(%esi),%edx
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
     91b:	0f ac d9 0c          	shrd   $0xc,%ebx,%ecx
static int rx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "rx_ch2_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
     91f:	89 44 24 04          	mov    %eax,0x4(%esp)
     923:	8b 46 08             	mov    0x8(%esi),%eax
     926:	2b 46 04             	sub    0x4(%esi),%eax
     929:	89 04 24             	mov    %eax,(%esp)
     92c:	89 f0                	mov    %esi,%eax
     92e:	e8 fc ff ff ff       	call   92f <rx_ch2_buffer_mmap+0x55>
	        (yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
	        vma->vm_end - vma->vm_start,
	        vma->vm_page_prot
	        );
	return err;
}
     933:	83 c4 0c             	add    $0xc,%esp
     936:	5b                   	pop    %ebx
     937:	5e                   	pop    %esi
     938:	5d                   	pop    %ebp
     939:	c3                   	ret    

0000093a <rx_ch1_buffer_mmap>:
	        );
	return err;
}

static int rx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
     93a:	55                   	push   %ebp
     93b:	89 e5                	mov    %esp,%ebp
     93d:	56                   	push   %esi
     93e:	53                   	push   %ebx
     93f:	83 ec 0c             	sub    $0xc,%esp
     942:	e8 fc ff ff ff       	call   943 <rx_ch1_buffer_mmap+0x9>
	int err;
	printk(KERN_INFO "rx_ch1_buffer mmap\n" );
     947:	c7 04 24 2d 07 00 00 	movl   $0x72d,(%esp)
	        );
	return err;
}

static int rx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
     94e:	89 d6                	mov    %edx,%esi
	int err;
	printk(KERN_INFO "rx_ch1_buffer mmap\n" );
     950:	e8 fc ff ff ff       	call   951 <rx_ch1_buffer_mmap+0x17>
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
     955:	a1 00 00 00 00       	mov    0x0,%eax

static int rx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "rx_ch1_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
     95a:	8b 4e 4c             	mov    0x4c(%esi),%ecx
	err = remap_pfn_range( vma,
     95d:	8b 56 18             	mov    0x18(%esi),%edx
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
     960:	8b 40 2c             	mov    0x2c(%eax),%eax

static int rx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "rx_ch1_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
     963:	c1 e1 0c             	shl    $0xc,%ecx
	err = remap_pfn_range( vma,
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
     966:	89 cb                	mov    %ecx,%ebx
     968:	c1 fb 1f             	sar    $0x1f,%ebx
     96b:	03 48 08             	add    0x8(%eax),%ecx
     96e:	13 58 0c             	adc    0xc(%eax),%ebx
static int rx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "rx_ch1_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
     971:	8b 46 14             	mov    0x14(%esi),%eax
     974:	89 54 24 08          	mov    %edx,0x8(%esp)
     978:	8b 56 04             	mov    0x4(%esi),%edx
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
     97b:	0f ac d9 0c          	shrd   $0xc,%ebx,%ecx
static int rx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "rx_ch1_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
     97f:	89 44 24 04          	mov    %eax,0x4(%esp)
     983:	8b 46 08             	mov    0x8(%esi),%eax
     986:	2b 46 04             	sub    0x4(%esi),%eax
     989:	89 04 24             	mov    %eax,(%esp)
     98c:	89 f0                	mov    %esi,%eax
     98e:	e8 fc ff ff ff       	call   98f <rx_ch1_buffer_mmap+0x55>
	        (yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
	        vma->vm_end - vma->vm_start,
	        vma->vm_page_prot
	        );
	return err;
}
     993:	83 c4 0c             	add    $0xc,%esp
     996:	5b                   	pop    %ebx
     997:	5e                   	pop    %esi
     998:	5d                   	pop    %ebp
     999:	c3                   	ret    

0000099a <tx_ch2_buffer_mmap>:
	        );
	return err;
}

static int tx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
     99a:	55                   	push   %ebp
     99b:	89 e5                	mov    %esp,%ebp
     99d:	56                   	push   %esi
     99e:	53                   	push   %ebx
     99f:	83 ec 0c             	sub    $0xc,%esp
     9a2:	e8 fc ff ff ff       	call   9a3 <tx_ch2_buffer_mmap+0x9>
	int err;
	printk(KERN_INFO "tx_ch2_buffer mmap\n" );
     9a7:	c7 04 24 44 07 00 00 	movl   $0x744,(%esp)
	        );
	return err;
}

static int tx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
     9ae:	89 d6                	mov    %edx,%esi
	int err;
	printk(KERN_INFO "tx_ch2_buffer mmap\n" );
     9b0:	e8 fc ff ff ff       	call   9b1 <tx_ch2_buffer_mmap+0x17>
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
     9b5:	a1 00 00 00 00       	mov    0x0,%eax

static int tx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "tx_ch2_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
     9ba:	8b 4e 4c             	mov    0x4c(%esi),%ecx
	err = remap_pfn_range( vma,
     9bd:	8b 56 18             	mov    0x18(%esi),%edx
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
     9c0:	8b 40 28             	mov    0x28(%eax),%eax

static int tx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "tx_ch2_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
     9c3:	c1 e1 0c             	shl    $0xc,%ecx
	err = remap_pfn_range( vma,
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
     9c6:	89 cb                	mov    %ecx,%ebx
     9c8:	c1 fb 1f             	sar    $0x1f,%ebx
     9cb:	03 48 08             	add    0x8(%eax),%ecx
     9ce:	13 58 0c             	adc    0xc(%eax),%ebx
static int tx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "tx_ch2_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
     9d1:	8b 46 14             	mov    0x14(%esi),%eax
     9d4:	89 54 24 08          	mov    %edx,0x8(%esp)
     9d8:	8b 56 04             	mov    0x4(%esi),%edx
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
     9db:	0f ac d9 0c          	shrd   $0xc,%ebx,%ecx
static int tx_ch2_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "tx_ch2_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
     9df:	89 44 24 04          	mov    %eax,0x4(%esp)
     9e3:	8b 46 08             	mov    0x8(%esi),%eax
     9e6:	2b 46 04             	sub    0x4(%esi),%eax
     9e9:	89 04 24             	mov    %eax,(%esp)
     9ec:	89 f0                	mov    %esi,%eax
     9ee:	e8 fc ff ff ff       	call   9ef <tx_ch2_buffer_mmap+0x55>
	        (yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
	        vma->vm_end - vma->vm_start,
	        vma->vm_page_prot
	        );
	return err;
}
     9f3:	83 c4 0c             	add    $0xc,%esp
     9f6:	5b                   	pop    %ebx
     9f7:	5e                   	pop    %esi
     9f8:	5d                   	pop    %ebp
     9f9:	c3                   	ret    

000009fa <tx_ch1_buffer_mmap>:
	&ProcWriteIrqInterval,

};

static int tx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
     9fa:	55                   	push   %ebp
     9fb:	89 e5                	mov    %esp,%ebp
     9fd:	56                   	push   %esi
     9fe:	53                   	push   %ebx
     9ff:	83 ec 0c             	sub    $0xc,%esp
     a02:	e8 fc ff ff ff       	call   a03 <tx_ch1_buffer_mmap+0x9>
	int err;
	printk(KERN_INFO "tx_ch1_buffer mmap\n" );
     a07:	c7 04 24 5b 07 00 00 	movl   $0x75b,(%esp)
	&ProcWriteIrqInterval,

};

static int tx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
     a0e:	89 d6                	mov    %edx,%esi
	int err;
	printk(KERN_INFO "tx_ch1_buffer mmap\n" );
     a10:	e8 fc ff ff ff       	call   a11 <tx_ch1_buffer_mmap+0x17>
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
     a15:	a1 00 00 00 00       	mov    0x0,%eax

static int tx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "tx_ch1_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
     a1a:	8b 4e 4c             	mov    0x4c(%esi),%ecx
	err = remap_pfn_range( vma,
     a1d:	8b 56 18             	mov    0x18(%esi),%edx
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
     a20:	8b 40 24             	mov    0x24(%eax),%eax

static int tx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "tx_ch1_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
     a23:	c1 e1 0c             	shl    $0xc,%ecx
	err = remap_pfn_range( vma,
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
     a26:	89 cb                	mov    %ecx,%ebx
     a28:	c1 fb 1f             	sar    $0x1f,%ebx
     a2b:	03 48 08             	add    0x8(%eax),%ecx
     a2e:	13 58 0c             	adc    0xc(%eax),%ebx
static int tx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "tx_ch1_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
     a31:	8b 46 14             	mov    0x14(%esi),%eax
     a34:	89 54 24 08          	mov    %edx,0x8(%esp)
     a38:	8b 56 04             	mov    0x4(%esi),%edx
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
     a3b:	0f ac d9 0c          	shrd   $0xc,%ebx,%ecx
static int tx_ch1_buffer_mmap(struct file *file, struct vm_area_struct * vma)
{
	int err;
	printk(KERN_INFO "tx_ch1_buffer mmap\n" );
	long int offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
     a3f:	89 44 24 04          	mov    %eax,0x4(%esp)
     a43:	8b 46 08             	mov    0x8(%esi),%eax
     a46:	2b 46 04             	sub    0x4(%esi),%eax
     a49:	89 04 24             	mov    %eax,(%esp)
     a4c:	89 f0                	mov    %esi,%eax
     a4e:	e8 fc ff ff ff       	call   a4f <tx_ch1_buffer_mmap+0x55>
	        (yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
	        vma->vm_end - vma->vm_start,
	        vma->vm_page_prot
	        );
	return err;
}
     a53:	83 c4 0c             	add    $0xc,%esp
     a56:	5b                   	pop    %ebx
     a57:	5e                   	pop    %esi
     a58:	5d                   	pop    %ebp
     a59:	c3                   	ret    

00000a5a <register_proc_files>:
};

static struct proc_dir_entry *yadma_proc_dir = NULL;

void register_proc_files()
{
     a5a:	55                   	push   %ebp
     a5b:	89 e5                	mov    %esp,%ebp
     a5d:	56                   	push   %esi
     a5e:	53                   	push   %ebx
     a5f:	83 ec 0c             	sub    $0xc,%esp
     a62:	e8 fc ff ff ff       	call   a63 <register_proc_files+0x9>
	int i;


	yadma_proc_dir = proc_mkdir(DRIVER_NAME, NULL );
     a67:	31 d2                	xor    %edx,%edx
     a69:	b8 72 07 00 00       	mov    $0x772,%eax

	/* Create control files */
	for(i = MAX_CHANS; i < MAX_FILES + MAX_CHANS; i++) {
     a6e:	bb 04 00 00 00       	mov    $0x4,%ebx
void register_proc_files()
{
	int i;


	yadma_proc_dir = proc_mkdir(DRIVER_NAME, NULL );
     a73:	e8 fc ff ff ff       	call   a74 <register_proc_files+0x1a>
     a78:	a3 80 00 00 00       	mov    %eax,0x80

	/* Create control files */
	for(i = MAX_CHANS; i < MAX_FILES + MAX_CHANS; i++) {
		struct proc_dir_entry *file = create_proc_entry(yadmaFileNames[i], YADMA_PROC_ACESS_RIGHTS, yadma_proc_dir);
     a7d:	8b 34 9d d0 01 00 00 	mov    0x1d0(,%ebx,4),%esi
     a84:	ba b6 01 00 00       	mov    $0x1b6,%edx
     a89:	8b 0d 80 00 00 00    	mov    0x80,%ecx
     a8f:	89 f0                	mov    %esi,%eax
     a91:	e8 fc ff ff ff       	call   a92 <register_proc_files+0x38>

		if ( file == NULL ) {
     a96:	85 c0                	test   %eax,%eax
     a98:	75 02                	jne    a9c <register_proc_files+0x42>
     a9a:	eb 64                	jmp    b00 <register_proc_files+0xa6>
			printk(KERN_ALERT "Error: Could not initialize /proc/%s/%s\n",
				YADMA_PROC_DIR,
			    yadmaFileNames[i]);
			return;
		} else {
			file->read_proc = yadmaProcReadFuncs[i];
     a9c:	8b 14 9d 1c 02 00 00 	mov    0x21c(,%ebx,4),%edx
     aa3:	89 50 34             	mov    %edx,0x34(%eax)
			file->write_proc = yadmaProcWriteFuncs[i];
     aa6:	8b 14 9d 68 02 00 00 	mov    0x268(,%ebx,4),%edx


	yadma_proc_dir = proc_mkdir(DRIVER_NAME, NULL );

	/* Create control files */
	for(i = MAX_CHANS; i < MAX_FILES + MAX_CHANS; i++) {
     aad:	43                   	inc    %ebx
				YADMA_PROC_DIR,
			    yadmaFileNames[i]);
			return;
		} else {
			file->read_proc = yadmaProcReadFuncs[i];
			file->write_proc = yadmaProcWriteFuncs[i];
     aae:	89 50 38             	mov    %edx,0x38(%eax)
            log_verbose(KERN_INFO "Create procfs /proc/%s/%s\n", YADMA_PROC_DIR, yadmaFileNames[i]);
     ab1:	89 74 24 08          	mov    %esi,0x8(%esp)
     ab5:	c7 44 24 04 78 07 00 	movl   $0x778,0x4(%esp)
     abc:	00 
     abd:	c7 04 24 b0 07 00 00 	movl   $0x7b0,(%esp)
     ac4:	e8 fc ff ff ff       	call   ac5 <register_proc_files+0x6b>


	yadma_proc_dir = proc_mkdir(DRIVER_NAME, NULL );

	/* Create control files */
	for(i = MAX_CHANS; i < MAX_FILES + MAX_CHANS; i++) {
     ac9:	83 fb 13             	cmp    $0x13,%ebx
     acc:	75 af                	jne    a7d <register_proc_files+0x23>
     ace:	30 db                	xor    %bl,%bl
	}

	/* Create buffer files */
	for(i = 0; i < MAX_CHANS; i++) {

		struct proc_dir_entry *file = proc_create_data(yadmaFileNames[i], YADMA_PROC_ACESS_RIGHTS, yadma_proc_dir, &yadmaBufFileOp[i], NULL);
     ad0:	6b c3 68             	imul   $0x68,%ebx,%eax
     ad3:	8b 34 9d d0 01 00 00 	mov    0x1d0(,%ebx,4),%esi
     ada:	ba b6 01 00 00       	mov    $0x1b6,%edx
     adf:	8b 0d 80 00 00 00    	mov    0x80,%ecx
     ae5:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
     aec:	00 
     aed:	05 00 00 00 00       	add    $0x0,%eax
     af2:	89 04 24             	mov    %eax,(%esp)
     af5:	89 f0                	mov    %esi,%eax
     af7:	e8 fc ff ff ff       	call   af8 <register_proc_files+0x9e>

		if ( file == NULL ) {
     afc:	85 c0                	test   %eax,%eax
     afe:	75 26                	jne    b26 <register_proc_files+0xcc>
			/* remove all enties under /proc/yadma */
			remove_proc_entry(YADMA_PROC_DIR, NULL );
     b00:	31 d2                	xor    %edx,%edx
     b02:	b8 78 07 00 00       	mov    $0x778,%eax
     b07:	e8 fc ff ff ff       	call   b08 <register_proc_files+0xae>
			printk(KERN_ALERT "Error: Could not initialize /proc/%s/%s\n",
     b0c:	89 74 24 08          	mov    %esi,0x8(%esp)
     b10:	c7 44 24 04 78 07 00 	movl   $0x778,0x4(%esp)
     b17:	00 
     b18:	c7 04 24 84 07 00 00 	movl   $0x784,(%esp)
     b1f:	e8 fc ff ff ff       	call   b20 <register_proc_files+0xc6>
				YADMA_PROC_DIR,
			    yadmaFileNames[i]);
			return;
     b24:	eb 1e                	jmp    b44 <register_proc_files+0xea>
		} else {
           log_verbose(KERN_INFO "Create procfs /proc/%s/%s\n", YADMA_PROC_DIR, yadmaFileNames[i]);
     b26:	89 74 24 08          	mov    %esi,0x8(%esp)
            log_verbose(KERN_INFO "Create procfs /proc/%s/%s\n", YADMA_PROC_DIR, yadmaFileNames[i]);
		}
	}

	/* Create buffer files */
	for(i = 0; i < MAX_CHANS; i++) {
     b2a:	43                   	inc    %ebx
			printk(KERN_ALERT "Error: Could not initialize /proc/%s/%s\n",
				YADMA_PROC_DIR,
			    yadmaFileNames[i]);
			return;
		} else {
           log_verbose(KERN_INFO "Create procfs /proc/%s/%s\n", YADMA_PROC_DIR, yadmaFileNames[i]);
     b2b:	c7 44 24 04 78 07 00 	movl   $0x778,0x4(%esp)
     b32:	00 
     b33:	c7 04 24 b0 07 00 00 	movl   $0x7b0,(%esp)
     b3a:	e8 fc ff ff ff       	call   b3b <register_proc_files+0xe1>
            log_verbose(KERN_INFO "Create procfs /proc/%s/%s\n", YADMA_PROC_DIR, yadmaFileNames[i]);
		}
	}

	/* Create buffer files */
	for(i = 0; i < MAX_CHANS; i++) {
     b3f:	83 fb 04             	cmp    $0x4,%ebx
     b42:	75 8c                	jne    ad0 <register_proc_files+0x76>
			return;
		} else {
           log_verbose(KERN_INFO "Create procfs /proc/%s/%s\n", YADMA_PROC_DIR, yadmaFileNames[i]);
        }
	}
}
     b44:	83 c4 0c             	add    $0xc,%esp
     b47:	5b                   	pop    %ebx
     b48:	5e                   	pop    %esi
     b49:	5d                   	pop    %ebp
     b4a:	c3                   	ret    

00000b4b <unregister_proc_files>:

void unregister_proc_files(void)
{
     b4b:	55                   	push   %ebp
     b4c:	89 e5                	mov    %esp,%ebp
     b4e:	53                   	push   %ebx
     b4f:	83 ec 08             	sub    $0x8,%esp
     b52:	e8 fc ff ff ff       	call   b53 <unregister_proc_files+0x8>
	int i;
	for( i=0;i<YADMA_FILE_COUNT;i++ ) {
     b57:	31 db                	xor    %ebx,%ebx
		remove_proc_entry(yadmaFileNames[i], yadma_proc_dir);
     b59:	8b 04 9d d0 01 00 00 	mov    0x1d0(,%ebx,4),%eax
}

void unregister_proc_files(void)
{
	int i;
	for( i=0;i<YADMA_FILE_COUNT;i++ ) {
     b60:	43                   	inc    %ebx
		remove_proc_entry(yadmaFileNames[i], yadma_proc_dir);
     b61:	8b 15 80 00 00 00    	mov    0x80,%edx
     b67:	e8 fc ff ff ff       	call   b68 <unregister_proc_files+0x1d>
}

void unregister_proc_files(void)
{
	int i;
	for( i=0;i<YADMA_FILE_COUNT;i++ ) {
     b6c:	83 fb 13             	cmp    $0x13,%ebx
     b6f:	75 e8                	jne    b59 <unregister_proc_files+0xe>
		remove_proc_entry(yadmaFileNames[i], yadma_proc_dir);
	}

	remove_proc_entry(DRIVER_NAME, NULL);
     b71:	31 d2                	xor    %edx,%edx
     b73:	b8 72 07 00 00       	mov    $0x772,%eax
     b78:	e8 fc ff ff ff       	call   b79 <unregister_proc_files+0x2e>
	printk(KERN_INFO "%s are removed.\n",YADMA_PROC_DIR);
     b7d:	c7 44 24 04 78 07 00 	movl   $0x778,0x4(%esp)
     b84:	00 
     b85:	c7 04 24 ce 07 00 00 	movl   $0x7ce,(%esp)
     b8c:	e8 fc ff ff ff       	call   b8d <unregister_proc_files+0x42>

}
     b91:	59                   	pop    %ecx
     b92:	5b                   	pop    %ebx
     b93:	5b                   	pop    %ebx
     b94:	5d                   	pop    %ebp
     b95:	c3                   	ret    
     b96:	66 90                	xchg   %ax,%ax

00000b98 <set_fpga_reset>:
	return 0;
}


ssize_t set_fpga_reset(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     b98:	55                   	push   %ebp
     b99:	89 e5                	mov    %esp,%ebp
     b9b:	83 ec 0c             	sub    $0xc,%esp
     b9e:	e8 fc ff ff ff       	call   b9f <set_fpga_reset+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     ba3:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     ba7:	c7 44 24 04 90 07 00 	movl   $0x790,0x4(%esp)
     bae:	00 
     baf:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     bb6:	e8 fc ff ff ff       	call   bb7 <set_fpga_reset+0x1f>
	return 0;
}
     bbb:	31 c0                	xor    %eax,%eax
     bbd:	c9                   	leave  
     bbe:	c3                   	ret    

00000bbf <show_fpga_reset>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_fpga_reset(struct device *dev, struct device_attribute *attr, char *buf)
{
     bbf:	55                   	push   %ebp
     bc0:	89 e5                	mov    %esp,%ebp
     bc2:	83 ec 0c             	sub    $0xc,%esp
     bc5:	e8 fc ff ff ff       	call   bc6 <show_fpga_reset+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     bca:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     bce:	c7 44 24 04 80 07 00 	movl   $0x780,0x4(%esp)
     bd5:	00 
     bd6:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     bdd:	e8 fc ff ff ff       	call   bde <show_fpga_reset+0x1f>
	return 0;
}
     be2:	31 c0                	xor    %eax,%eax
     be4:	c9                   	leave  
     be5:	c3                   	ret    

00000be6 <set_sys_timing>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_sys_timing(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     be6:	55                   	push   %ebp
     be7:	89 e5                	mov    %esp,%ebp
     be9:	83 ec 0c             	sub    $0xc,%esp
     bec:	e8 fc ff ff ff       	call   bed <set_sys_timing+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     bf1:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     bf5:	c7 44 24 04 70 07 00 	movl   $0x770,0x4(%esp)
     bfc:	00 
     bfd:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     c04:	e8 fc ff ff ff       	call   c05 <set_sys_timing+0x1f>
	return 0;
}
     c09:	31 c0                	xor    %eax,%eax
     c0b:	c9                   	leave  
     c0c:	c3                   	ret    

00000c0d <show_sys_timing>:
}

/*-------------------------------------Timing and Reset ---------------------------------------*/

ssize_t show_sys_timing(struct device *dev, struct device_attribute *attr, char *buf)
{
     c0d:	55                   	push   %ebp
     c0e:	89 e5                	mov    %esp,%ebp
     c10:	83 ec 0c             	sub    $0xc,%esp
     c13:	e8 fc ff ff ff       	call   c14 <show_sys_timing+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     c18:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     c1c:	c7 44 24 04 60 07 00 	movl   $0x760,0x4(%esp)
     c23:	00 
     c24:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     c2b:	e8 fc ff ff ff       	call   c2c <show_sys_timing+0x1f>
	return 0;
}
     c30:	31 c0                	xor    %eax,%eax
     c32:	c9                   	leave  
     c33:	c3                   	ret    

00000c34 <set_rx2_rf_state>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx2_rf_state(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     c34:	55                   	push   %ebp
     c35:	89 e5                	mov    %esp,%ebp
     c37:	83 ec 0c             	sub    $0xc,%esp
     c3a:	e8 fc ff ff ff       	call   c3b <set_rx2_rf_state+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     c3f:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     c43:	c7 44 24 04 4c 07 00 	movl   $0x74c,0x4(%esp)
     c4a:	00 
     c4b:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     c52:	e8 fc ff ff ff       	call   c53 <set_rx2_rf_state+0x1f>
	return 0;
}
     c57:	31 c0                	xor    %eax,%eax
     c59:	c9                   	leave  
     c5a:	c3                   	ret    

00000c5b <show_rx2_rf_state>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx2_rf_state(struct device *dev, struct device_attribute *attr, char *buf)
{
     c5b:	55                   	push   %ebp
     c5c:	89 e5                	mov    %esp,%ebp
     c5e:	83 ec 0c             	sub    $0xc,%esp
     c61:	e8 fc ff ff ff       	call   c62 <show_rx2_rf_state+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     c66:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     c6a:	c7 44 24 04 38 07 00 	movl   $0x738,0x4(%esp)
     c71:	00 
     c72:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     c79:	e8 fc ff ff ff       	call   c7a <show_rx2_rf_state+0x1f>
	return 0;
}
     c7e:	31 c0                	xor    %eax,%eax
     c80:	c9                   	leave  
     c81:	c3                   	ret    

00000c82 <set_rx1_rf_state>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx1_rf_state(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     c82:	55                   	push   %ebp
     c83:	89 e5                	mov    %esp,%ebp
     c85:	83 ec 0c             	sub    $0xc,%esp
     c88:	e8 fc ff ff ff       	call   c89 <set_rx1_rf_state+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     c8d:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     c91:	c7 44 24 04 24 07 00 	movl   $0x724,0x4(%esp)
     c98:	00 
     c99:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     ca0:	e8 fc ff ff ff       	call   ca1 <set_rx1_rf_state+0x1f>
	return 0;
}
     ca5:	31 c0                	xor    %eax,%eax
     ca7:	c9                   	leave  
     ca8:	c3                   	ret    

00000ca9 <show_rx1_rf_state>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx1_rf_state(struct device *dev, struct device_attribute *attr, char *buf)
{
     ca9:	55                   	push   %ebp
     caa:	89 e5                	mov    %esp,%ebp
     cac:	83 ec 0c             	sub    $0xc,%esp
     caf:	e8 fc ff ff ff       	call   cb0 <show_rx1_rf_state+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     cb4:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     cb8:	c7 44 24 04 10 07 00 	movl   $0x710,0x4(%esp)
     cbf:	00 
     cc0:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     cc7:	e8 fc ff ff ff       	call   cc8 <show_rx1_rf_state+0x1f>
	return 0;
}
     ccc:	31 c0                	xor    %eax,%eax
     cce:	c9                   	leave  
     ccf:	c3                   	ret    

00000cd0 <set_tx2_rssi>:
	return 0;
}


ssize_t set_tx2_rssi(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     cd0:	55                   	push   %ebp
     cd1:	89 e5                	mov    %esp,%ebp
     cd3:	83 ec 0c             	sub    $0xc,%esp
     cd6:	e8 fc ff ff ff       	call   cd7 <set_tx2_rssi+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     cdb:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     cdf:	c7 44 24 04 00 07 00 	movl   $0x700,0x4(%esp)
     ce6:	00 
     ce7:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     cee:	e8 fc ff ff ff       	call   cef <set_tx2_rssi+0x1f>
	return 0;
}
     cf3:	31 c0                	xor    %eax,%eax
     cf5:	c9                   	leave  
     cf6:	c3                   	ret    

00000cf7 <show_tx2_rssi>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_tx2_rssi(struct device *dev, struct device_attribute *attr, char *buf)
{
     cf7:	55                   	push   %ebp
     cf8:	89 e5                	mov    %esp,%ebp
     cfa:	83 ec 0c             	sub    $0xc,%esp
     cfd:	e8 fc ff ff ff       	call   cfe <show_tx2_rssi+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     d02:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     d06:	c7 44 24 04 f0 06 00 	movl   $0x6f0,0x4(%esp)
     d0d:	00 
     d0e:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     d15:	e8 fc ff ff ff       	call   d16 <show_tx2_rssi+0x1f>
	return 0;
}
     d1a:	31 c0                	xor    %eax,%eax
     d1c:	c9                   	leave  
     d1d:	c3                   	ret    

00000d1e <set_tx1_rssi>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_tx1_rssi(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     d1e:	55                   	push   %ebp
     d1f:	89 e5                	mov    %esp,%ebp
     d21:	83 ec 0c             	sub    $0xc,%esp
     d24:	e8 fc ff ff ff       	call   d25 <set_tx1_rssi+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     d29:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     d2d:	c7 44 24 04 e0 06 00 	movl   $0x6e0,0x4(%esp)
     d34:	00 
     d35:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     d3c:	e8 fc ff ff ff       	call   d3d <set_tx1_rssi+0x1f>
	return 0;
}
     d41:	31 c0                	xor    %eax,%eax
     d43:	c9                   	leave  
     d44:	c3                   	ret    

00000d45 <show_tx1_rssi>:
	return 0;
}

/*-------------------------------------RSSI and State-----------------------------------------*/
ssize_t show_tx1_rssi(struct device *dev, struct device_attribute *attr, char *buf)
{
     d45:	55                   	push   %ebp
     d46:	89 e5                	mov    %esp,%ebp
     d48:	83 ec 0c             	sub    $0xc,%esp
     d4b:	e8 fc ff ff ff       	call   d4c <show_tx1_rssi+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     d50:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     d54:	c7 44 24 04 d0 06 00 	movl   $0x6d0,0x4(%esp)
     d5b:	00 
     d5c:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     d63:	e8 fc ff ff ff       	call   d64 <show_tx1_rssi+0x1f>
	return 0;
}
     d68:	31 c0                	xor    %eax,%eax
     d6a:	c9                   	leave  
     d6b:	c3                   	ret    

00000d6c <set_rx2_gain>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx2_gain(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     d6c:	55                   	push   %ebp
     d6d:	89 e5                	mov    %esp,%ebp
     d6f:	83 ec 0c             	sub    $0xc,%esp
     d72:	e8 fc ff ff ff       	call   d73 <set_rx2_gain+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     d77:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     d7b:	c7 44 24 04 c0 06 00 	movl   $0x6c0,0x4(%esp)
     d82:	00 
     d83:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     d8a:	e8 fc ff ff ff       	call   d8b <set_rx2_gain+0x1f>
	return 0;
}
     d8f:	31 c0                	xor    %eax,%eax
     d91:	c9                   	leave  
     d92:	c3                   	ret    

00000d93 <show_rx2_gain>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx2_gain(struct device *dev, struct device_attribute *attr, char *buf)
{
     d93:	55                   	push   %ebp
     d94:	89 e5                	mov    %esp,%ebp
     d96:	83 ec 0c             	sub    $0xc,%esp
     d99:	e8 fc ff ff ff       	call   d9a <show_rx2_gain+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     d9e:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     da2:	c7 44 24 04 b0 06 00 	movl   $0x6b0,0x4(%esp)
     da9:	00 
     daa:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     db1:	e8 fc ff ff ff       	call   db2 <show_rx2_gain+0x1f>
	return 0;
}
     db6:	31 c0                	xor    %eax,%eax
     db8:	c9                   	leave  
     db9:	c3                   	ret    

00000dba <set_rx1_gain>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx1_gain(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     dba:	55                   	push   %ebp
     dbb:	89 e5                	mov    %esp,%ebp
     dbd:	83 ec 0c             	sub    $0xc,%esp
     dc0:	e8 fc ff ff ff       	call   dc1 <set_rx1_gain+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     dc5:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     dc9:	c7 44 24 04 a0 06 00 	movl   $0x6a0,0x4(%esp)
     dd0:	00 
     dd1:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     dd8:	e8 fc ff ff ff       	call   dd9 <set_rx1_gain+0x1f>
	return 0;
}
     ddd:	31 c0                	xor    %eax,%eax
     ddf:	c9                   	leave  
     de0:	c3                   	ret    

00000de1 <show_rx1_gain>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx1_gain(struct device *dev, struct device_attribute *attr, char *buf)
{
     de1:	55                   	push   %ebp
     de2:	89 e5                	mov    %esp,%ebp
     de4:	83 ec 0c             	sub    $0xc,%esp
     de7:	e8 fc ff ff ff       	call   de8 <show_rx1_gain+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     dec:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     df0:	c7 44 24 04 90 06 00 	movl   $0x690,0x4(%esp)
     df7:	00 
     df8:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     dff:	e8 fc ff ff ff       	call   e00 <show_rx1_gain+0x1f>
	return 0;
}
     e04:	31 c0                	xor    %eax,%eax
     e06:	c9                   	leave  
     e07:	c3                   	ret    

00000e08 <set_tx2_gain>:
	return 0;
}


ssize_t set_tx2_gain(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     e08:	55                   	push   %ebp
     e09:	89 e5                	mov    %esp,%ebp
     e0b:	83 ec 0c             	sub    $0xc,%esp
     e0e:	e8 fc ff ff ff       	call   e0f <set_tx2_gain+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     e13:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     e17:	c7 44 24 04 80 06 00 	movl   $0x680,0x4(%esp)
     e1e:	00 
     e1f:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     e26:	e8 fc ff ff ff       	call   e27 <set_tx2_gain+0x1f>
	return 0;
}
     e2b:	31 c0                	xor    %eax,%eax
     e2d:	c9                   	leave  
     e2e:	c3                   	ret    

00000e2f <show_tx2_gain>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_tx2_gain(struct device *dev, struct device_attribute *attr, char *buf)
{
     e2f:	55                   	push   %ebp
     e30:	89 e5                	mov    %esp,%ebp
     e32:	83 ec 0c             	sub    $0xc,%esp
     e35:	e8 fc ff ff ff       	call   e36 <show_tx2_gain+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     e3a:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     e3e:	c7 44 24 04 70 06 00 	movl   $0x670,0x4(%esp)
     e45:	00 
     e46:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     e4d:	e8 fc ff ff ff       	call   e4e <show_tx2_gain+0x1f>
	return 0;
}
     e52:	31 c0                	xor    %eax,%eax
     e54:	c9                   	leave  
     e55:	c3                   	ret    

00000e56 <set_tx1_gain>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_tx1_gain(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     e56:	55                   	push   %ebp
     e57:	89 e5                	mov    %esp,%ebp
     e59:	83 ec 0c             	sub    $0xc,%esp
     e5c:	e8 fc ff ff ff       	call   e5d <set_tx1_gain+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     e61:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     e65:	c7 44 24 04 60 06 00 	movl   $0x660,0x4(%esp)
     e6c:	00 
     e6d:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     e74:	e8 fc ff ff ff       	call   e75 <set_tx1_gain+0x1f>
	return 0;
}
     e79:	31 c0                	xor    %eax,%eax
     e7b:	c9                   	leave  
     e7c:	c3                   	ret    

00000e7d <show_tx1_gain>:
	return 0;
}

/*-------------------------------------RF Gain-----------------------------------------*/
ssize_t show_tx1_gain(struct device *dev, struct device_attribute *attr, char *buf)
{
     e7d:	55                   	push   %ebp
     e7e:	89 e5                	mov    %esp,%ebp
     e80:	83 ec 0c             	sub    $0xc,%esp
     e83:	e8 fc ff ff ff       	call   e84 <show_tx1_gain+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     e88:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     e8c:	c7 44 24 04 50 06 00 	movl   $0x650,0x4(%esp)
     e93:	00 
     e94:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     e9b:	e8 fc ff ff ff       	call   e9c <show_tx1_gain+0x1f>
	return 0;
}
     ea0:	31 c0                	xor    %eax,%eax
     ea2:	c9                   	leave  
     ea3:	c3                   	ret    

00000ea4 <set_rx2_freq>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx2_freq(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     ea4:	55                   	push   %ebp
     ea5:	89 e5                	mov    %esp,%ebp
     ea7:	83 ec 0c             	sub    $0xc,%esp
     eaa:	e8 fc ff ff ff       	call   eab <set_rx2_freq+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     eaf:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     eb3:	c7 44 24 04 40 06 00 	movl   $0x640,0x4(%esp)
     eba:	00 
     ebb:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     ec2:	e8 fc ff ff ff       	call   ec3 <set_rx2_freq+0x1f>
	return 0;
}
     ec7:	31 c0                	xor    %eax,%eax
     ec9:	c9                   	leave  
     eca:	c3                   	ret    

00000ecb <show_rx2_freq>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx2_freq(struct device *dev, struct device_attribute *attr, char *buf)
{
     ecb:	55                   	push   %ebp
     ecc:	89 e5                	mov    %esp,%ebp
     ece:	83 ec 0c             	sub    $0xc,%esp
     ed1:	e8 fc ff ff ff       	call   ed2 <show_rx2_freq+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     ed6:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     eda:	c7 44 24 04 30 06 00 	movl   $0x630,0x4(%esp)
     ee1:	00 
     ee2:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     ee9:	e8 fc ff ff ff       	call   eea <show_rx2_freq+0x1f>
	return 0;
}
     eee:	31 c0                	xor    %eax,%eax
     ef0:	c9                   	leave  
     ef1:	c3                   	ret    

00000ef2 <set_rx1_freq>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx1_freq(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     ef2:	55                   	push   %ebp
     ef3:	89 e5                	mov    %esp,%ebp
     ef5:	83 ec 0c             	sub    $0xc,%esp
     ef8:	e8 fc ff ff ff       	call   ef9 <set_rx1_freq+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     efd:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     f01:	c7 44 24 04 20 06 00 	movl   $0x620,0x4(%esp)
     f08:	00 
     f09:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     f10:	e8 fc ff ff ff       	call   f11 <set_rx1_freq+0x1f>
	return 0;
}
     f15:	31 c0                	xor    %eax,%eax
     f17:	c9                   	leave  
     f18:	c3                   	ret    

00000f19 <show_rx1_freq>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx1_freq(struct device *dev, struct device_attribute *attr, char *buf)
{
     f19:	55                   	push   %ebp
     f1a:	89 e5                	mov    %esp,%ebp
     f1c:	83 ec 0c             	sub    $0xc,%esp
     f1f:	e8 fc ff ff ff       	call   f20 <show_rx1_freq+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     f24:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     f28:	c7 44 24 04 10 06 00 	movl   $0x610,0x4(%esp)
     f2f:	00 
     f30:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     f37:	e8 fc ff ff ff       	call   f38 <show_rx1_freq+0x1f>
	return 0;
}
     f3c:	31 c0                	xor    %eax,%eax
     f3e:	c9                   	leave  
     f3f:	c3                   	ret    

00000f40 <set_tx2_freq>:
	return 0;
}


ssize_t set_tx2_freq(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     f40:	55                   	push   %ebp
     f41:	89 e5                	mov    %esp,%ebp
     f43:	83 ec 0c             	sub    $0xc,%esp
     f46:	e8 fc ff ff ff       	call   f47 <set_tx2_freq+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     f4b:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     f4f:	c7 44 24 04 00 06 00 	movl   $0x600,0x4(%esp)
     f56:	00 
     f57:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     f5e:	e8 fc ff ff ff       	call   f5f <set_tx2_freq+0x1f>
	return 0;
}
     f63:	31 c0                	xor    %eax,%eax
     f65:	c9                   	leave  
     f66:	c3                   	ret    

00000f67 <show_tx2_freq>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_tx2_freq(struct device *dev, struct device_attribute *attr, char *buf)
{
     f67:	55                   	push   %ebp
     f68:	89 e5                	mov    %esp,%ebp
     f6a:	83 ec 0c             	sub    $0xc,%esp
     f6d:	e8 fc ff ff ff       	call   f6e <show_tx2_freq+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     f72:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     f76:	c7 44 24 04 f0 05 00 	movl   $0x5f0,0x4(%esp)
     f7d:	00 
     f7e:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     f85:	e8 fc ff ff ff       	call   f86 <show_tx2_freq+0x1f>
	return 0;
}
     f8a:	31 c0                	xor    %eax,%eax
     f8c:	c9                   	leave  
     f8d:	c3                   	ret    

00000f8e <set_tx1_freq>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_tx1_freq(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     f8e:	55                   	push   %ebp
     f8f:	89 e5                	mov    %esp,%ebp
     f91:	83 ec 0c             	sub    $0xc,%esp
     f94:	e8 fc ff ff ff       	call   f95 <set_tx1_freq+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     f99:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     f9d:	c7 44 24 04 e0 05 00 	movl   $0x5e0,0x4(%esp)
     fa4:	00 
     fa5:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     fac:	e8 fc ff ff ff       	call   fad <set_tx1_freq+0x1f>
	return 0;
}
     fb1:	31 c0                	xor    %eax,%eax
     fb3:	c9                   	leave  
     fb4:	c3                   	ret    

00000fb5 <show_tx1_freq>:
	return 0;
}

/*-------------------------------------FREQ point -----------------------------------------*/
ssize_t show_tx1_freq(struct device *dev, struct device_attribute *attr, char *buf)
{
     fb5:	55                   	push   %ebp
     fb6:	89 e5                	mov    %esp,%ebp
     fb8:	83 ec 0c             	sub    $0xc,%esp
     fbb:	e8 fc ff ff ff       	call   fbc <show_tx1_freq+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     fc0:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     fc4:	c7 44 24 04 d0 05 00 	movl   $0x5d0,0x4(%esp)
     fcb:	00 
     fcc:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     fd3:	e8 fc ff ff ff       	call   fd4 <show_tx1_freq+0x1f>
	return 0;
}
     fd8:	31 c0                	xor    %eax,%eax
     fda:	c9                   	leave  
     fdb:	c3                   	ret    

00000fdc <set_irq_interval>:
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_irq_interval(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
     fdc:	55                   	push   %ebp
     fdd:	89 e5                	mov    %esp,%ebp
     fdf:	83 ec 0c             	sub    $0xc,%esp
     fe2:	e8 fc ff ff ff       	call   fe3 <set_irq_interval+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
     fe7:	89 4c 24 08          	mov    %ecx,0x8(%esp)
     feb:	c7 44 24 04 bc 05 00 	movl   $0x5bc,0x4(%esp)
     ff2:	00 
     ff3:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
     ffa:	e8 fc ff ff ff       	call   ffb <set_irq_interval+0x1f>
	return 0;
}
     fff:	31 c0                	xor    %eax,%eax
    1001:	c9                   	leave  
    1002:	c3                   	ret    

00001003 <show_irq_interval>:



/*-------------------------------------IRQ Interval-----------------------------------------*/
ssize_t show_irq_interval(struct device *dev, struct device_attribute *attr, char *buf)
{
    1003:	55                   	push   %ebp
    1004:	89 e5                	mov    %esp,%ebp
    1006:	83 ec 0c             	sub    $0xc,%esp
    1009:	e8 fc ff ff ff       	call   100a <show_irq_interval+0x7>
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
    100e:	89 4c 24 08          	mov    %ecx,0x8(%esp)
    1012:	c7 44 24 04 a8 05 00 	movl   $0x5a8,0x4(%esp)
    1019:	00 
    101a:	c7 04 24 9c 08 00 00 	movl   $0x89c,(%esp)
    1021:	e8 fc ff ff ff       	call   1022 <show_irq_interval+0x1f>
	return 0;
}
    1026:	31 c0                	xor    %eax,%eax
    1028:	c9                   	leave  
    1029:	c3                   	ret    

0000102a <rx_mem_ch2_mmap>:
			vma->vm_page_prot
			);
	return err;
}
static int rx_mem_ch2_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
    102a:	55                   	push   %ebp
    102b:	89 e5                	mov    %esp,%ebp
    102d:	56                   	push   %esi
    102e:	53                   	push   %ebx
    102f:	83 ec 0c             	sub    $0xc,%esp
    1032:	e8 fc ff ff ff       	call   1033 <rx_mem_ch2_mmap+0x9>
    1037:	8b 75 08             	mov    0x8(%ebp),%esi
	int err;
    long int offset;
	printk(KERN_INFO "rx_mem_ch2 mmap\n" );
    103a:	c7 04 24 b5 08 00 00 	movl   $0x8b5,(%esp)
    1041:	e8 fc ff ff ff       	call   1042 <rx_mem_ch2_mmap+0x18>
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
			vma->vm_start,
			(yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
    1046:	a1 00 00 00 00       	mov    0x0,%eax
static int rx_mem_ch2_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;
    long int offset;
	printk(KERN_INFO "rx_mem_ch2 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
    104b:	8b 4e 4c             	mov    0x4c(%esi),%ecx
	err = remap_pfn_range( vma,
    104e:	8b 56 18             	mov    0x18(%esi),%edx
			vma->vm_start,
			(yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
    1051:	8b 40 30             	mov    0x30(%eax),%eax
static int rx_mem_ch2_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;
    long int offset;
	printk(KERN_INFO "rx_mem_ch2 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
    1054:	c1 e1 0c             	shl    $0xc,%ecx
	err = remap_pfn_range( vma,
			vma->vm_start,
			(yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
    1057:	89 cb                	mov    %ecx,%ebx
    1059:	c1 fb 1f             	sar    $0x1f,%ebx
    105c:	03 48 08             	add    0x8(%eax),%ecx
    105f:	13 58 0c             	adc    0xc(%eax),%ebx
{
	int err;
    long int offset;
	printk(KERN_INFO "rx_mem_ch2 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
    1062:	8b 46 14             	mov    0x14(%esi),%eax
    1065:	89 54 24 08          	mov    %edx,0x8(%esp)
			vma->vm_start,
			(yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
    1069:	0f ac d9 0c          	shrd   $0xc,%ebx,%ecx
{
	int err;
    long int offset;
	printk(KERN_INFO "rx_mem_ch2 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
    106d:	89 44 24 04          	mov    %eax,0x4(%esp)
    1071:	8b 46 08             	mov    0x8(%esi),%eax
    1074:	2b 46 04             	sub    0x4(%esi),%eax
    1077:	89 04 24             	mov    %eax,(%esp)
    107a:	8b 56 04             	mov    0x4(%esi),%edx
    107d:	89 f0                	mov    %esi,%eax
    107f:	e8 fc ff ff ff       	call   1080 <rx_mem_ch2_mmap+0x56>
			(yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
			vma->vm_end - vma->vm_start,
			vma->vm_page_prot
			);
	return err;
}
    1084:	83 c4 0c             	add    $0xc,%esp
    1087:	5b                   	pop    %ebx
    1088:	5e                   	pop    %esi
    1089:	5d                   	pop    %ebp
    108a:	c3                   	ret    

0000108b <rx_mem_ch1_mmap>:
			vma->vm_page_prot
			);
	return err;
}
static int rx_mem_ch1_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
    108b:	55                   	push   %ebp
    108c:	89 e5                	mov    %esp,%ebp
    108e:	56                   	push   %esi
    108f:	53                   	push   %ebx
    1090:	83 ec 0c             	sub    $0xc,%esp
    1093:	e8 fc ff ff ff       	call   1094 <rx_mem_ch1_mmap+0x9>
    1098:	8b 75 08             	mov    0x8(%ebp),%esi
	int err;
    long int offset;
	printk(KERN_INFO "rx_mem_ch1 mmap\n" );
    109b:	c7 04 24 c9 08 00 00 	movl   $0x8c9,(%esp)
    10a2:	e8 fc ff ff ff       	call   10a3 <rx_mem_ch1_mmap+0x18>
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
			vma->vm_start,
			(yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
    10a7:	a1 00 00 00 00       	mov    0x0,%eax
static int rx_mem_ch1_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;
    long int offset;
	printk(KERN_INFO "rx_mem_ch1 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
    10ac:	8b 4e 4c             	mov    0x4c(%esi),%ecx
	err = remap_pfn_range( vma,
    10af:	8b 56 18             	mov    0x18(%esi),%edx
			vma->vm_start,
			(yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
    10b2:	8b 40 2c             	mov    0x2c(%eax),%eax
static int rx_mem_ch1_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;
    long int offset;
	printk(KERN_INFO "rx_mem_ch1 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
    10b5:	c1 e1 0c             	shl    $0xc,%ecx
	err = remap_pfn_range( vma,
			vma->vm_start,
			(yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
    10b8:	89 cb                	mov    %ecx,%ebx
    10ba:	c1 fb 1f             	sar    $0x1f,%ebx
    10bd:	03 48 08             	add    0x8(%eax),%ecx
    10c0:	13 58 0c             	adc    0xc(%eax),%ebx
{
	int err;
    long int offset;
	printk(KERN_INFO "rx_mem_ch1 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
    10c3:	8b 46 14             	mov    0x14(%esi),%eax
    10c6:	89 54 24 08          	mov    %edx,0x8(%esp)
			vma->vm_start,
			(yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
    10ca:	0f ac d9 0c          	shrd   $0xc,%ebx,%ecx
{
	int err;
    long int offset;
	printk(KERN_INFO "rx_mem_ch1 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
    10ce:	89 44 24 04          	mov    %eax,0x4(%esp)
    10d2:	8b 46 08             	mov    0x8(%esi),%eax
    10d5:	2b 46 04             	sub    0x4(%esi),%eax
    10d8:	89 04 24             	mov    %eax,(%esp)
    10db:	8b 56 04             	mov    0x4(%esi),%edx
    10de:	89 f0                	mov    %esi,%eax
    10e0:	e8 fc ff ff ff       	call   10e1 <rx_mem_ch1_mmap+0x56>
			(yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
			vma->vm_end - vma->vm_start,
			vma->vm_page_prot
			);
	return err;
}
    10e5:	83 c4 0c             	add    $0xc,%esp
    10e8:	5b                   	pop    %ebx
    10e9:	5e                   	pop    %esi
    10ea:	5d                   	pop    %ebp
    10eb:	c3                   	ret    

000010ec <tx_mem_ch2_mmap>:
			vma->vm_page_prot
			);
	return err;
}
static int tx_mem_ch2_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
    10ec:	55                   	push   %ebp
    10ed:	89 e5                	mov    %esp,%ebp
    10ef:	56                   	push   %esi
    10f0:	53                   	push   %ebx
    10f1:	83 ec 0c             	sub    $0xc,%esp
    10f4:	e8 fc ff ff ff       	call   10f5 <tx_mem_ch2_mmap+0x9>
    10f9:	8b 75 08             	mov    0x8(%ebp),%esi
	int err;
    long int offset;
	printk(KERN_INFO "tx_mem_ch2 mmap\n" );
    10fc:	c7 04 24 dd 08 00 00 	movl   $0x8dd,(%esp)
    1103:	e8 fc ff ff ff       	call   1104 <tx_mem_ch2_mmap+0x18>
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
			vma->vm_start,
			(yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
    1108:	a1 00 00 00 00       	mov    0x0,%eax
static int tx_mem_ch2_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;
    long int offset;
	printk(KERN_INFO "tx_mem_ch2 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
    110d:	8b 4e 4c             	mov    0x4c(%esi),%ecx
	err = remap_pfn_range( vma,
    1110:	8b 56 18             	mov    0x18(%esi),%edx
			vma->vm_start,
			(yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
    1113:	8b 40 28             	mov    0x28(%eax),%eax
static int tx_mem_ch2_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;
    long int offset;
	printk(KERN_INFO "tx_mem_ch2 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
    1116:	c1 e1 0c             	shl    $0xc,%ecx
	err = remap_pfn_range( vma,
			vma->vm_start,
			(yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
    1119:	89 cb                	mov    %ecx,%ebx
    111b:	c1 fb 1f             	sar    $0x1f,%ebx
    111e:	03 48 08             	add    0x8(%eax),%ecx
    1121:	13 58 0c             	adc    0xc(%eax),%ebx
{
	int err;
    long int offset;
	printk(KERN_INFO "tx_mem_ch2 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
    1124:	8b 46 14             	mov    0x14(%esi),%eax
    1127:	89 54 24 08          	mov    %edx,0x8(%esp)
			vma->vm_start,
			(yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
    112b:	0f ac d9 0c          	shrd   $0xc,%ebx,%ecx
{
	int err;
    long int offset;
	printk(KERN_INFO "tx_mem_ch2 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
    112f:	89 44 24 04          	mov    %eax,0x4(%esp)
    1133:	8b 46 08             	mov    0x8(%esi),%eax
    1136:	2b 46 04             	sub    0x4(%esi),%eax
    1139:	89 04 24             	mov    %eax,(%esp)
    113c:	8b 56 04             	mov    0x4(%esi),%edx
    113f:	89 f0                	mov    %esi,%eax
    1141:	e8 fc ff ff ff       	call   1142 <tx_mem_ch2_mmap+0x56>
			(yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr + offset) >> PAGE_SHIFT,
			vma->vm_end - vma->vm_start,
			vma->vm_page_prot
			);
	return err;
}
    1146:	83 c4 0c             	add    $0xc,%esp
    1149:	5b                   	pop    %ebx
    114a:	5e                   	pop    %esi
    114b:	5d                   	pop    %ebp
    114c:	c3                   	ret    

0000114d <tx_mem_ch1_mmap>:
};


/* sysfs bin_attributes are used to be mmapped into userspace */
static int tx_mem_ch1_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
    114d:	55                   	push   %ebp
    114e:	89 e5                	mov    %esp,%ebp
    1150:	56                   	push   %esi
    1151:	53                   	push   %ebx
    1152:	83 ec 0c             	sub    $0xc,%esp
    1155:	e8 fc ff ff ff       	call   1156 <tx_mem_ch1_mmap+0x9>
    115a:	8b 75 08             	mov    0x8(%ebp),%esi
	int err;
    long int offset;
	printk(KERN_INFO "tx_mem_ch1 mmap\n" );
    115d:	c7 04 24 f1 08 00 00 	movl   $0x8f1,(%esp)
    1164:	e8 fc ff ff ff       	call   1165 <tx_mem_ch1_mmap+0x18>
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
			vma->vm_start,
			(yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
    1169:	a1 00 00 00 00       	mov    0x0,%eax
static int tx_mem_ch1_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;
    long int offset;
	printk(KERN_INFO "tx_mem_ch1 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
    116e:	8b 4e 4c             	mov    0x4c(%esi),%ecx
	err = remap_pfn_range( vma,
    1171:	8b 56 18             	mov    0x18(%esi),%edx
			vma->vm_start,
			(yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
    1174:	8b 40 24             	mov    0x24(%eax),%eax
static int tx_mem_ch1_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;
    long int offset;
	printk(KERN_INFO "tx_mem_ch1 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
    1177:	c1 e1 0c             	shl    $0xc,%ecx
	err = remap_pfn_range( vma,
			vma->vm_start,
			(yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
    117a:	89 cb                	mov    %ecx,%ebx
    117c:	c1 fb 1f             	sar    $0x1f,%ebx
    117f:	03 48 08             	add    0x8(%eax),%ecx
    1182:	13 58 0c             	adc    0xc(%eax),%ebx
{
	int err;
    long int offset;
	printk(KERN_INFO "tx_mem_ch1 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
    1185:	8b 46 14             	mov    0x14(%esi),%eax
    1188:	89 54 24 08          	mov    %edx,0x8(%esp)
			vma->vm_start,
			(yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
    118c:	0f ac d9 0c          	shrd   $0xc,%ebx,%ecx
{
	int err;
    long int offset;
	printk(KERN_INFO "tx_mem_ch1 mmap\n" );
	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
    1190:	89 44 24 04          	mov    %eax,0x4(%esp)
    1194:	8b 46 08             	mov    0x8(%esi),%eax
    1197:	2b 46 04             	sub    0x4(%esi),%eax
    119a:	89 04 24             	mov    %eax,(%esp)
    119d:	8b 56 04             	mov    0x4(%esi),%edx
    11a0:	89 f0                	mov    %esi,%eax
    11a2:	e8 fc ff ff ff       	call   11a3 <tx_mem_ch1_mmap+0x56>
			(yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr + offset) >> PAGE_SHIFT,
			vma->vm_end - vma->vm_start,
			vma->vm_page_prot
			);
	return err;
}
    11a7:	83 c4 0c             	add    $0xc,%esp
    11aa:	5b                   	pop    %ebx
    11ab:	5e                   	pop    %esi
    11ac:	5d                   	pop    %ebp
    11ad:	c3                   	ret    

000011ae <register_sysfs_files>:
		.attrs = dev_attrs,
};


void register_sysfs_files(struct kobject *kobj)
{
    11ae:	55                   	push   %ebp
    11af:	89 e5                	mov    %esp,%ebp
    11b1:	57                   	push   %edi
    11b2:	56                   	push   %esi
    11b3:	53                   	push   %ebx
    11b4:	83 ec 08             	sub    $0x8,%esp
    11b7:	e8 fc ff ff ff       	call   11b8 <register_sysfs_files+0xa>
	int i, ret;

	/* Create control files */
	ret = sysfs_create_group(kobj, &yadma_dev_attr_grp);
    11bc:	ba 18 01 00 00       	mov    $0x118,%edx
		.attrs = dev_attrs,
};


void register_sysfs_files(struct kobject *kobj)
{
    11c1:	89 c6                	mov    %eax,%esi
	int i, ret;

	/* Create control files */
	ret = sysfs_create_group(kobj, &yadma_dev_attr_grp);
    11c3:	e8 fc ff ff ff       	call   11c4 <register_sysfs_files+0x16>
	if (ret) {
    11c8:	85 c0                	test   %eax,%eax
    11ca:	74 11                	je     11dd <register_sysfs_files+0x2f>
		printk(KERN_ERR, "Failed to create sysfs device attributes\n");
    11cc:	c7 44 24 04 05 09 00 	movl   $0x905,0x4(%esp)
    11d3:	00 
    11d4:	c7 04 24 2f 09 00 00 	movl   $0x92f,(%esp)
    11db:	eb 10                	jmp    11ed <register_sysfs_files+0x3f>
	} else {
		printk(KERN_INFO "Attribute group %s are created.\n",yadma_dev_attr_grp.name);
    11dd:	a1 18 01 00 00       	mov    0x118,%eax
    11e2:	c7 04 24 33 09 00 00 	movl   $0x933,(%esp)
    11e9:	89 44 24 04          	mov    %eax,0x4(%esp)
    11ed:	e8 fc ff ff ff       	call   11ee <register_sysfs_files+0x40>
		.attrs = dev_attrs,
};


void register_sysfs_files(struct kobject *kobj)
{
    11f2:	31 db                	xor    %ebx,%ebx
		printk(KERN_INFO "Attribute group %s are created.\n",yadma_dev_attr_grp.name);
	}

	/* Create buffer files */
	for(i = 0; i < MAX_CHANS; i++) {
		ret = sysfs_create_bin_file(kobj, bin_attrs_group[i]);
    11f4:	8b 3c 9d a0 07 00 00 	mov    0x7a0(,%ebx,4),%edi
    11fb:	89 f0                	mov    %esi,%eax
    11fd:	89 fa                	mov    %edi,%edx
    11ff:	e8 fc ff ff ff       	call   1200 <register_sysfs_files+0x52>
		if (ret) {
    1204:	85 c0                	test   %eax,%eax
    1206:	74 0e                	je     1216 <register_sysfs_files+0x68>
			printk(KERN_ERR "Failed to create sys file/n");
    1208:	c7 04 24 57 09 00 00 	movl   $0x957,(%esp)
    120f:	e8 fc ff ff ff       	call   1210 <register_sysfs_files+0x62>
    1214:	eb 12                	jmp    1228 <register_sysfs_files+0x7a>
		} else {
			printk(KERN_INFO "Bin Attribute %s are created.\n",bin_attrs_group[i]->attr.name);
    1216:	8b 07                	mov    (%edi),%eax
    1218:	c7 04 24 76 09 00 00 	movl   $0x976,(%esp)
    121f:	89 44 24 04          	mov    %eax,0x4(%esp)
    1223:	e8 fc ff ff ff       	call   1224 <register_sysfs_files+0x76>
	} else {
		printk(KERN_INFO "Attribute group %s are created.\n",yadma_dev_attr_grp.name);
	}

	/* Create buffer files */
	for(i = 0; i < MAX_CHANS; i++) {
    1228:	43                   	inc    %ebx
    1229:	83 fb 04             	cmp    $0x4,%ebx
    122c:	75 c6                	jne    11f4 <register_sysfs_files+0x46>
			printk(KERN_ERR "Failed to create sys file/n");
		} else {
			printk(KERN_INFO "Bin Attribute %s are created.\n",bin_attrs_group[i]->attr.name);
		}
	}
}
    122e:	58                   	pop    %eax
    122f:	5a                   	pop    %edx
    1230:	5b                   	pop    %ebx
    1231:	5e                   	pop    %esi
    1232:	5f                   	pop    %edi
    1233:	5d                   	pop    %ebp
    1234:	c3                   	ret    

00001235 <unregister_sysfs_files>:

void unregister_sysfs_files(struct kobject *kobj)
{
    1235:	55                   	push   %ebp
    1236:	89 e5                	mov    %esp,%ebp
    1238:	57                   	push   %edi
    1239:	56                   	push   %esi
    123a:	53                   	push   %ebx
    123b:	83 ec 08             	sub    $0x8,%esp
    123e:	e8 fc ff ff ff       	call   123f <unregister_sysfs_files+0xa>
	int i, ret;

    /* remove the registered sysfs attributes */
    sysfs_remove_group(kobj, &yadma_dev_attr_grp);
    1243:	ba 18 01 00 00       	mov    $0x118,%edx

	printk(KERN_INFO "Attribute group %s are removed.\n",yadma_dev_attr_grp.name);

	/* remove buffer files */
	for(i = 0; i < MAX_CHANS; i++) {
    1248:	31 db                	xor    %ebx,%ebx
		}
	}
}

void unregister_sysfs_files(struct kobject *kobj)
{
    124a:	89 c6                	mov    %eax,%esi
	int i, ret;

    /* remove the registered sysfs attributes */
    sysfs_remove_group(kobj, &yadma_dev_attr_grp);
    124c:	e8 fc ff ff ff       	call   124d <unregister_sysfs_files+0x18>

	printk(KERN_INFO "Attribute group %s are removed.\n",yadma_dev_attr_grp.name);
    1251:	a1 18 01 00 00       	mov    0x118,%eax
    1256:	c7 04 24 98 09 00 00 	movl   $0x998,(%esp)
    125d:	89 44 24 04          	mov    %eax,0x4(%esp)
    1261:	e8 fc ff ff ff       	call   1262 <unregister_sysfs_files+0x2d>

	/* remove buffer files */
	for(i = 0; i < MAX_CHANS; i++) {
		sysfs_remove_bin_file(kobj, bin_attrs_group[i]);
    1266:	8b 3c 9d a0 07 00 00 	mov    0x7a0(,%ebx,4),%edi
    126d:	89 f0                	mov    %esi,%eax
    sysfs_remove_group(kobj, &yadma_dev_attr_grp);

	printk(KERN_INFO "Attribute group %s are removed.\n",yadma_dev_attr_grp.name);

	/* remove buffer files */
	for(i = 0; i < MAX_CHANS; i++) {
    126f:	43                   	inc    %ebx
		sysfs_remove_bin_file(kobj, bin_attrs_group[i]);
    1270:	89 fa                	mov    %edi,%edx
    1272:	e8 fc ff ff ff       	call   1273 <unregister_sysfs_files+0x3e>
		printk(KERN_INFO "Remove sys bin_attribute file %s.\n", bin_attrs_group[i]->attr.name);
    1277:	8b 07                	mov    (%edi),%eax
    1279:	c7 04 24 bc 09 00 00 	movl   $0x9bc,(%esp)
    1280:	89 44 24 04          	mov    %eax,0x4(%esp)
    1284:	e8 fc ff ff ff       	call   1285 <unregister_sysfs_files+0x50>
    sysfs_remove_group(kobj, &yadma_dev_attr_grp);

	printk(KERN_INFO "Attribute group %s are removed.\n",yadma_dev_attr_grp.name);

	/* remove buffer files */
	for(i = 0; i < MAX_CHANS; i++) {
    1289:	83 fb 04             	cmp    $0x4,%ebx
    128c:	75 d8                	jne    1266 <unregister_sysfs_files+0x31>
		sysfs_remove_bin_file(kobj, bin_attrs_group[i]);
		printk(KERN_INFO "Remove sys bin_attribute file %s.\n", bin_attrs_group[i]->attr.name);
	}
}
    128e:	5b                   	pop    %ebx
    128f:	5e                   	pop    %esi
    1290:	5b                   	pop    %ebx
    1291:	5e                   	pop    %esi
    1292:	5f                   	pop    %edi
    1293:	5d                   	pop    %ebp
    1294:	c3                   	ret    

Disassembly of section .text.unlikely:

00000000 <yadma_destroy_channel.part.4>:
 *  Caller should warrant no DMA hardware still use the buffers.
 *
 *  @chan The DMA channel to be free.
 */

static void yadma_destroy_channel(struct device *dev, DmaChannel* chan)
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	57                   	push   %edi
   4:	56                   	push   %esi
   5:	53                   	push   %ebx
   6:	83 ec 24             	sub    $0x24,%esp
   9:	e8 fc ff ff ff       	call   a <yadma_destroy_channel.part.4+0xa>
   e:	89 45 ec             	mov    %eax,-0x14(%ebp)
{

	if(chan) {
        log_verbose(KERN_INFO "Free a DMA Buffer size: %d, virt %p, phys %p.\n", \
  11:	8b 42 08             	mov    0x8(%edx),%eax
 *  Caller should warrant no DMA hardware still use the buffers.
 *
 *  @chan The DMA channel to be free.
 */

static void yadma_destroy_channel(struct device *dev, DmaChannel* chan)
  14:	89 d3                	mov    %edx,%ebx
{

	if(chan) {
        log_verbose(KERN_INFO "Free a DMA Buffer size: %d, virt %p, phys %p.\n", \
  16:	8b 52 0c             	mov    0xc(%edx),%edx
  19:	c7 04 24 94 00 00 00 	movl   $0x94,(%esp)
  20:	89 44 24 0c          	mov    %eax,0xc(%esp)
  24:	8b 43 10             	mov    0x10(%ebx),%eax
  27:	89 54 24 10          	mov    %edx,0x10(%esp)
  2b:	89 44 24 08          	mov    %eax,0x8(%esp)
  2f:	8b 43 14             	mov    0x14(%ebx),%eax
  32:	89 44 24 04          	mov    %eax,0x4(%esp)
  36:	e8 fc ff ff ff       	call   37 <yadma_destroy_channel.part.4+0x37>
                chan->total_length, chan->virt_addr, chan->phys_addr);

		dma_free_coherent(dev, chan->total_length, chan->virt_addr, chan->phys_addr);
  3b:	8b 53 0c             	mov    0xc(%ebx),%edx
	long tmp = -1;
	asm("bsrl %1,%0"
	    : "=r" (r)
	    : "rm" (x), "0" (tmp));
#elif defined(CONFIG_X86_CMOV)
	asm("bsrl %1,%0\n\t"
  3e:	83 c9 ff             	or     $0xffffffff,%ecx
  41:	8b 43 08             	mov    0x8(%ebx),%eax
  44:	8b 7b 14             	mov    0x14(%ebx),%edi
extern struct dma_map_ops *dma_ops;

static inline struct dma_map_ops *get_dma_ops(struct device *dev)
{
#ifndef CONFIG_X86_DEV_DMA_OPS
	return dma_ops;
  47:	8b 35 00 00 00 00    	mov    0x0,%esi
  4d:	89 55 e8             	mov    %edx,-0x18(%ebp)
  50:	8b 53 10             	mov    0x10(%ebx),%edx
  53:	89 45 e4             	mov    %eax,-0x1c(%ebp)
static inline __attribute_const__
int __get_order(unsigned long size)
{
	int order;

	size--;
  56:	8d 47 ff             	lea    -0x1(%edi),%eax
	size >>= PAGE_SHIFT;
  59:	c1 e8 0c             	shr    $0xc,%eax
  5c:	89 55 f0             	mov    %edx,-0x10(%ebp)
  5f:	0f bd d0             	bsr    %eax,%edx
  62:	0f 44 d1             	cmove  %ecx,%edx
				  void *vaddr, dma_addr_t bus,
				  struct dma_attrs *attrs)
{
	struct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_release_from_coherent(dev, get_order(size), vaddr))
  65:	8b 4d f0             	mov    -0x10(%ebp),%ecx
	asm("bsrl %1,%0\n\t"
	    "jnz 1f\n\t"
	    "movl $-1,%0\n"
	    "1:" : "=r" (r) : "rm" (x));
#endif
	return r + 1;
  68:	42                   	inc    %edx
  69:	8b 45 ec             	mov    -0x14(%ebp),%eax
  6c:	e8 fc ff ff ff       	call   6d <yadma_destroy_channel.part.4+0x6d>
  71:	85 c0                	test   %eax,%eax
  73:	75 26                	jne    9b <yadma_destroy_channel.part.4+0x9b>
		return;

	debug_dma_free_coherent(dev, size, vaddr, bus);
	if (ops->free)
  75:	8b 76 04             	mov    0x4(%esi),%esi
  78:	85 f6                	test   %esi,%esi
  7a:	74 1f                	je     9b <yadma_destroy_channel.part.4+0x9b>
		ops->free(dev, size, vaddr, bus, attrs);
  7c:	8b 45 e4             	mov    -0x1c(%ebp),%eax
  7f:	8b 55 e8             	mov    -0x18(%ebp),%edx
  82:	8b 4d f0             	mov    -0x10(%ebp),%ecx
  85:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  8c:	00 
  8d:	89 04 24             	mov    %eax,(%esp)
  90:	8b 45 ec             	mov    -0x14(%ebp),%eax
  93:	89 54 24 04          	mov    %edx,0x4(%esp)
  97:	89 fa                	mov    %edi,%edx
  99:	ff d6                	call   *%esi
		kfree(chan);
  9b:	89 d8                	mov    %ebx,%eax
  9d:	e8 fc ff ff ff       	call   9e <yadma_destroy_channel.part.4+0x9e>
	}
}
  a2:	83 c4 24             	add    $0x24,%esp
  a5:	5b                   	pop    %ebx
  a6:	5e                   	pop    %esi
  a7:	5f                   	pop    %edi
  a8:	5d                   	pop    %ebp
  a9:	c3                   	ret    

Disassembly of section .devinit.text:

00000000 <yadma_pcie_probe>:
*/
/********************************************************************/
/*  PCI probing function */
/********************************************************************/
static int __devinit yadma_pcie_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
   0:	55                   	push   %ebp
   1:	ba 00 00 00 00       	mov    $0x0,%edx
   6:	89 e5                	mov    %esp,%ebp
   8:	57                   	push   %edi
   9:	56                   	push   %esi
   a:	53                   	push   %ebx
   b:	89 c3                	mov    %eax,%ebx
   d:	83 ec 30             	sub    $0x30,%esp
  10:	83 c0 60             	add    $0x60,%eax
  13:	0f 45 d0             	cmovne %eax,%edx
  16:	89 45 e0             	mov    %eax,-0x20(%ebp)
  19:	89 55 dc             	mov    %edx,-0x24(%ebp)
    int pciRet, chrRet;
    int i;

    /* Initialize DMA buffers that will be mapped with user space.
     */
    for(i=0; i<MAX_CHANS; i++)
  1c:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%ebp)
    {
        yadmaPrivData->dma_chans[i] = yadma_create_channel(&(pdev->dev), YADMA_BLOCK_COUNT, YADMA_SLOT_COUNT,YADMA_SLOT_SIZE);
  23:	a1 00 00 00 00       	mov    0x0,%eax
  28:	89 45 d8             	mov    %eax,-0x28(%ebp)
	int index = kmalloc_index(size);

	if (index == 0)
		return NULL;

	return kmalloc_caches[index];
  2b:	a1 18 00 00 00       	mov    0x18,%eax
			return kmalloc_large(size, flags);

		if (!(flags & SLUB_DMA)) {
			struct kmem_cache *s = kmalloc_slab(size);

			if (!s)
  30:	85 c0                	test   %eax,%eax
  32:	74 1b                	je     4f <yadma_pcie_probe+0x4f>
				return ZERO_SIZE_PTR;

			return kmem_cache_alloc_trace(s, flags, size);
  34:	b9 38 00 00 00       	mov    $0x38,%ecx
  39:	ba d0 00 00 00       	mov    $0xd0,%edx
  3e:	e8 fc ff ff ff       	call   3f <yadma_pcie_probe+0x3f>
	void* virt_addr;
	size_t length;


	DmaChannel *pch = kmalloc(sizeof(DmaChannel), GFP_KERNEL);
	if(pch){
  43:	85 c0                	test   %eax,%eax
  45:	89 c6                	mov    %eax,%esi
  47:	0f 84 05 01 00 00    	je     152 <yadma_pcie_probe+0x152>
  4d:	eb 05                	jmp    54 <yadma_pcie_probe+0x54>

		if (!(flags & SLUB_DMA)) {
			struct kmem_cache *s = kmalloc_slab(size);

			if (!s)
				return ZERO_SIZE_PTR;
  4f:	be 10 00 00 00       	mov    $0x10,%esi
	struct dma_map_ops *ops = get_dma_ops(dev);
	void *memory;

	gfp &= ~(__GFP_DMA | __GFP_HIGHMEM | __GFP_DMA32);

	if (dma_alloc_from_coherent(dev, size, dma_handle, &memory))
  54:	8b 45 e0             	mov    -0x20(%ebp),%eax
  57:	8d 55 e8             	lea    -0x18(%ebp),%edx
		spin_lock_init(&(pch->chnl_lock));
		pch->chnl_state = 0;
  5a:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  60:	8d 4d ec             	lea    -0x14(%ebp),%ecx
extern struct dma_map_ops *dma_ops;

static inline struct dma_map_ops *get_dma_ops(struct device *dev)
{
#ifndef CONFIG_X86_DEV_DMA_OPS
	return dma_ops;
  63:	8b 3d 00 00 00 00    	mov    0x0,%edi
	size_t length;


	DmaChannel *pch = kmalloc(sizeof(DmaChannel), GFP_KERNEL);
	if(pch){
		spin_lock_init(&(pch->chnl_lock));
  69:	66 c7 46 04 00 00    	movw   $0x0,0x4(%esi)
		pch->chnl_state = 0;
		pch->cur_block = 0;
  6f:	c7 46 28 00 00 00 00 	movl   $0x0,0x28(%esi)
		pch->cur_slot = 0;
  76:	c7 46 2c 00 00 00 00 	movl   $0x0,0x2c(%esi)
	struct dma_map_ops *ops = get_dma_ops(dev);
	void *memory;

	gfp &= ~(__GFP_DMA | __GFP_HIGHMEM | __GFP_DMA32);

	if (dma_alloc_from_coherent(dev, size, dma_handle, &memory))
  7d:	89 14 24             	mov    %edx,(%esp)
  80:	ba 00 84 03 00       	mov    $0x38400,%edx
  85:	e8 fc ff ff ff       	call   86 <yadma_pcie_probe+0x86>
  8a:	85 c0                	test   %eax,%eax
  8c:	74 05                	je     93 <yadma_pcie_probe+0x93>
		return memory;
  8e:	8b 7d e8             	mov    -0x18(%ebp),%edi
  91:	eb 58                	jmp    eb <yadma_pcie_probe+0xeb>
        return IRQ_NONE;
}


module_init(yadma_init);
module_exit(yadma_cleanup);
  93:	8b 55 dc             	mov    -0x24(%ebp),%edx
  96:	8b 82 0c 01 00 00    	mov    0x10c(%edx),%eax
		(dma_direction == DMA_FROM_DEVICE));
}

static inline int is_device_dma_capable(struct device *dev)
{
	return dev->dma_mask != NULL && *dev->dma_mask != DMA_MASK_NONE;
  9c:	85 c0                	test   %eax,%eax
  9e:	74 49                	je     e9 <yadma_pcie_probe+0xe9>
  a0:	8b 50 04             	mov    0x4(%eax),%edx
  a3:	0b 10                	or     (%eax),%edx
  a5:	0f 85 7e 04 00 00    	jne    529 <yadma_pcie_probe+0x529>
  ab:	eb 3c                	jmp    e9 <yadma_pcie_probe+0xe9>
static inline unsigned long dma_alloc_coherent_mask(struct device *dev,
						    gfp_t gfp)
{
	unsigned long dma_mask = 0;

	dma_mask = dev->coherent_dma_mask;
  ad:	8b 55 dc             	mov    -0x24(%ebp),%edx
  b0:	8b 82 10 01 00 00    	mov    0x110(%edx),%eax
	if (!dma_mask)
  b6:	85 c0                	test   %eax,%eax
  b8:	75 07                	jne    c1 <yadma_pcie_probe+0xc1>
  ba:	b8 20 00 00 00       	mov    $0x20,%eax
  bf:	eb 0c                	jmp    cd <yadma_pcie_probe+0xcd>

static inline gfp_t dma_alloc_coherent_gfp_flags(struct device *dev, gfp_t gfp)
{
	unsigned long dma_mask = dma_alloc_coherent_mask(dev, gfp);

	if (dma_mask <= DMA_BIT_MASK(24))
  c1:	3d ff ff ff 00       	cmp    $0xffffff,%eax
  c6:	77 f2                	ja     ba <yadma_pcie_probe+0xba>
		gfp |= GFP_DMA;
  c8:	b8 21 00 00 00       	mov    $0x21,%eax
		return NULL;

	if (!ops->alloc)
		return NULL;

	memory = ops->alloc(dev, size, dma_handle,
  cd:	89 04 24             	mov    %eax,(%esp)
  d0:	8b 45 dc             	mov    -0x24(%ebp),%eax
  d3:	8d 4d ec             	lea    -0x14(%ebp),%ecx
  d6:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
  dd:	00 
  de:	ba 00 84 03 00       	mov    $0x38400,%edx
  e3:	ff d7                	call   *%edi
  e5:	89 c7                	mov    %eax,%edi
  e7:	eb 02                	jmp    eb <yadma_pcie_probe+0xeb>

	if (!dev)
		dev = &x86_dma_fallback_dev;

	if (!is_device_dma_capable(dev))
		return NULL;
  e9:	31 ff                	xor    %edi,%edi
		pch->cur_slot = 0;

		/* allocate the physical continous memory for the buffer */
		length = bd_count * slot_count * slot_size;
		virt_addr = dma_alloc_coherent(dev, length, &phys_addr, GFP_ATOMIC);
        log_verbose(KERN_INFO "Allocated a DMA Buffer size: %d, virt %p, phys %p.\n", length, virt_addr, phys_addr);
  eb:	8b 45 ec             	mov    -0x14(%ebp),%eax
  ee:	8b 55 f0             	mov    -0x10(%ebp),%edx
  f1:	89 7c 24 08          	mov    %edi,0x8(%esp)
  f5:	c7 44 24 04 00 84 03 	movl   $0x38400,0x4(%esp)
  fc:	00 
  fd:	89 44 24 0c          	mov    %eax,0xc(%esp)
 101:	89 54 24 10          	mov    %edx,0x10(%esp)
 105:	c7 04 24 c6 00 00 00 	movl   $0xc6,(%esp)
 10c:	e8 fc ff ff ff       	call   10d <yadma_pcie_probe+0x10d>

        if(virt_addr) {
 111:	85 ff                	test   %edi,%edi
 113:	74 34                	je     149 <yadma_pcie_probe+0x149>
			pch->phys_addr = phys_addr;
 115:	8b 55 f0             	mov    -0x10(%ebp),%edx
 118:	8b 45 ec             	mov    -0x14(%ebp),%eax
			pch->virt_addr = virt_addr;
 11b:	89 7e 10             	mov    %edi,0x10(%esi)
			pch->total_length = length;
 11e:	c7 46 14 00 84 03 00 	movl   $0x38400,0x14(%esi)
		length = bd_count * slot_count * slot_size;
		virt_addr = dma_alloc_coherent(dev, length, &phys_addr, GFP_ATOMIC);
        log_verbose(KERN_INFO "Allocated a DMA Buffer size: %d, virt %p, phys %p.\n", length, virt_addr, phys_addr);

        if(virt_addr) {
			pch->phys_addr = phys_addr;
 125:	89 56 0c             	mov    %edx,0xc(%esi)
 128:	89 46 08             	mov    %eax,0x8(%esi)
			pch->virt_addr = virt_addr;
			pch->total_length = length;
			pch->slot_size = slot_size;
 12b:	c7 46 24 40 0b 00 00 	movl   $0xb40,0x24(%esi)
			pch->block_count = bd_count;
 132:	c7 46 18 02 00 00 00 	movl   $0x2,0x18(%esi)
			pch->block_size = slot_size * slot_count;
 139:	c7 46 1c 00 c2 01 00 	movl   $0x1c200,0x1c(%esi)
			pch->slot_count = slot_count;
 140:	c7 46 20 28 00 00 00 	movl   $0x28,0x20(%esi)
 147:	eb 09                	jmp    152 <yadma_pcie_probe+0x152>
		} else {
			kfree(pch);
 149:	89 f0                	mov    %esi,%eax
			return NULL;
 14b:	31 f6                	xor    %esi,%esi
			pch->slot_size = slot_size;
			pch->block_count = bd_count;
			pch->block_size = slot_size * slot_count;
			pch->slot_count = slot_count;
		} else {
			kfree(pch);
 14d:	e8 fc ff ff ff       	call   14e <yadma_pcie_probe+0x14e>

    /* Initialize DMA buffers that will be mapped with user space.
     */
    for(i=0; i<MAX_CHANS; i++)
    {
        yadmaPrivData->dma_chans[i] = yadma_create_channel(&(pdev->dev), YADMA_BLOCK_COUNT, YADMA_SLOT_COUNT,YADMA_SLOT_SIZE);
 152:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 155:	8b 55 d8             	mov    -0x28(%ebp),%edx
 158:	83 c0 08             	add    $0x8,%eax
 15b:	89 74 82 04          	mov    %esi,0x4(%edx,%eax,4)
        if(yadmaPrivData->dma_chans[i] == NULL) {
 15f:	8b 15 00 00 00 00    	mov    0x0,%edx
 165:	8b 44 82 04          	mov    0x4(%edx,%eax,4),%eax
 169:	85 c0                	test   %eax,%eax
 16b:	75 3f                	jne    1ac <yadma_pcie_probe+0x1ac>
            log_verbose(KERN_ERR "Unable to create DMA Channel %d.\n", i);
 16d:	8b 45 e4             	mov    -0x1c(%ebp),%eax
            for(i = 0; i < MAX_CHANS; i++) {
 170:	31 db                	xor    %ebx,%ebx
     */
    for(i=0; i<MAX_CHANS; i++)
    {
        yadmaPrivData->dma_chans[i] = yadma_create_channel(&(pdev->dev), YADMA_BLOCK_COUNT, YADMA_SLOT_COUNT,YADMA_SLOT_SIZE);
        if(yadmaPrivData->dma_chans[i] == NULL) {
            log_verbose(KERN_ERR "Unable to create DMA Channel %d.\n", i);
 172:	c7 04 24 fd 00 00 00 	movl   $0xfd,(%esp)
 179:	89 44 24 04          	mov    %eax,0x4(%esp)
 17d:	e8 fc ff ff ff       	call   17e <yadma_pcie_probe+0x17e>
            for(i = 0; i < MAX_CHANS; i++) {
                if(yadmaPrivData->dma_chans[i]) {
 182:	a1 00 00 00 00       	mov    0x0,%eax
 187:	8b 54 98 24          	mov    0x24(%eax,%ebx,4),%edx
 18b:	85 d2                	test   %edx,%edx
 18d:	74 08                	je     197 <yadma_pcie_probe+0x197>
 18f:	8b 45 e0             	mov    -0x20(%ebp),%eax
 192:	e8 fc ff ff ff       	call   193 <yadma_pcie_probe+0x193>
    for(i=0; i<MAX_CHANS; i++)
    {
        yadmaPrivData->dma_chans[i] = yadma_create_channel(&(pdev->dev), YADMA_BLOCK_COUNT, YADMA_SLOT_COUNT,YADMA_SLOT_SIZE);
        if(yadmaPrivData->dma_chans[i] == NULL) {
            log_verbose(KERN_ERR "Unable to create DMA Channel %d.\n", i);
            for(i = 0; i < MAX_CHANS; i++) {
 197:	43                   	inc    %ebx
 198:	83 fb 04             	cmp    $0x4,%ebx
 19b:	75 e5                	jne    182 <yadma_pcie_probe+0x182>
                if(yadmaPrivData->dma_chans[i]) {
                    yadma_destroy_channel(&(pdev->dev), yadmaPrivData->dma_chans[i]);
                }
            }
            kfree(yadmaPrivData);
 19d:	a1 00 00 00 00       	mov    0x0,%eax
 1a2:	e8 fc ff ff ff       	call   1a3 <yadma_pcie_probe+0x1a3>
 1a7:	e9 69 02 00 00       	jmp    415 <yadma_pcie_probe+0x415>
            return YADMA_FAILURE;
        } else {
#ifdef DEBUG_YADMA
        /* Fill in debug data */
        sprintf(yadmaPrivData->dma_chans[i], "Channel %d: %s", i, "1234567890");
 1ac:	8b 55 e4             	mov    -0x1c(%ebp),%edx
 1af:	c7 44 24 0c 22 01 00 	movl   $0x122,0xc(%esp)
 1b6:	00 
 1b7:	c7 44 24 04 2d 01 00 	movl   $0x12d,0x4(%esp)
 1be:	00 
 1bf:	89 04 24             	mov    %eax,(%esp)
 1c2:	89 54 24 08          	mov    %edx,0x8(%esp)
 1c6:	e8 fc ff ff ff       	call   1c7 <yadma_pcie_probe+0x1c7>
#endif
			log_verbose("Allocate DMA memory for channel %d success.\n");
 1cb:	c7 04 24 3c 01 00 00 	movl   $0x13c,(%esp)
 1d2:	e8 fc ff ff ff       	call   1d3 <yadma_pcie_probe+0x1d3>
    int pciRet, chrRet;
    int i;

    /* Initialize DMA buffers that will be mapped with user space.
     */
    for(i=0; i<MAX_CHANS; i++)
 1d7:	ff 45 e4             	incl   -0x1c(%ebp)
 1da:	83 7d e4 04          	cmpl   $0x4,-0x1c(%ebp)
 1de:	0f 85 3f fe ff ff    	jne    23 <yadma_pcie_probe+0x23>

    /* Initialize device before it is used by driver. Ask low-level
     * code to enable I/O and memory. Wake up the device if it was
     * suspended. Beware, this function can fail.
     */
	pciRet = pci_enable_device(pdev);
 1e4:	89 d8                	mov    %ebx,%eax
 1e6:	e8 fc ff ff ff       	call   1e7 <yadma_pcie_probe+0x1e7>
	if (pciRet < 0)
 1eb:	85 c0                	test   %eax,%eax

    /* Initialize device before it is used by driver. Ask low-level
     * code to enable I/O and memory. Wake up the device if it was
     * suspended. Beware, this function can fail.
     */
	pciRet = pci_enable_device(pdev);
 1ed:	89 c6                	mov    %eax,%esi
	if (pciRet < 0)
 1ef:	79 11                	jns    202 <yadma_pcie_probe+0x202>
	{
	    log_verbose(KERN_ERR "PCI device enable failed.\n");
 1f1:	c7 04 24 69 01 00 00 	movl   $0x169,(%esp)
 1f8:	e8 fc ff ff ff       	call   1f9 <yadma_pcie_probe+0x1f9>
	    return pciRet;
 1fd:	e9 36 03 00 00       	jmp    538 <yadma_pcie_probe+0x538>
	}
    else
    {
        log_verbose(KERN_INFO "PCI device enable success.\n");
 202:	c7 04 24 87 01 00 00 	movl   $0x187,(%esp)
 209:	e8 fc ff ff ff       	call   20a <yadma_pcie_probe+0x20a>
    }
    /*
     * Enable bus-mastering on device. Calls pcibios_set_master() to do
     * the needed architecture-specific settings.
     */
    log_verbose(KERN_INFO "PCI device is set as master.\n");
 20e:	c7 04 24 a6 01 00 00 	movl   $0x1a6,(%esp)
 215:	e8 fc ff ff ff       	call   216 <yadma_pcie_probe+0x216>
    pci_set_master(pdev);
 21a:	89 d8                	mov    %ebx,%eax
 21c:	e8 fc ff ff ff       	call   21d <yadma_pcie_probe+0x21d>
    /* Reserve PCI I/O and memory resources. Mark all PCI regions
     * associated with PCI device as being reserved by owner. Do not
     * access any address inside the PCI regions unless this call returns
     * successfully.
     */
    pciRet = pci_request_regions(pdev, DRIVER_NAME);
 221:	ba c7 01 00 00       	mov    $0x1c7,%edx
 226:	89 d8                	mov    %ebx,%eax
 228:	e8 fc ff ff ff       	call   229 <yadma_pcie_probe+0x229>
    if (pciRet < 0) {
 22d:	85 c0                	test   %eax,%eax
    /* Reserve PCI I/O and memory resources. Mark all PCI regions
     * associated with PCI device as being reserved by owner. Do not
     * access any address inside the PCI regions unless this call returns
     * successfully.
     */
    pciRet = pci_request_regions(pdev, DRIVER_NAME);
 22f:	89 c6                	mov    %eax,%esi
    if (pciRet < 0) {
 231:	79 0e                	jns    241 <yadma_pcie_probe+0x241>
        log_verbose(KERN_ERR "Could not request PCI regions.\n");
 233:	c7 04 24 cd 01 00 00 	movl   $0x1cd,(%esp)
 23a:	e8 fc ff ff ff       	call   23b <yadma_pcie_probe+0x23b>
 23f:	eb 32                	jmp    273 <yadma_pcie_probe+0x273>
        kfree(yadmaPrivData);
        pci_disable_device(pdev);
        return pciRet;
    } else {
        log_verbose(KERN_INFO "Request PCI regions success.\n");
 241:	c7 04 24 f0 01 00 00 	movl   $0x1f0,(%esp)
 248:	e8 fc ff ff ff       	call   249 <yadma_pcie_probe+0x249>
}

#ifdef CONFIG_PCI
static inline int pci_set_dma_mask(struct pci_dev *dev, u64 mask)
{
	return dma_set_mask(&dev->dev, mask);
 24d:	8b 45 e0             	mov    -0x20(%ebp),%eax
 250:	83 ca ff             	or     $0xffffffff,%edx
 253:	31 c9                	xor    %ecx,%ecx
 255:	e8 fc ff ff ff       	call   256 <yadma_pcie_probe+0x256>
    pciRet = pci_set_dma_mask(pdev, DMA_32BIT_MASK);
#else
    pciRet = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
#endif

    if (pciRet < 0) {
 25a:	85 c0                	test   %eax,%eax
 25c:	89 c6                	mov    %eax,%esi
 25e:	79 29                	jns    289 <yadma_pcie_probe+0x289>
        log_verbose(KERN_ERR "pci_set_dma_mask failed\n");
 260:	c7 04 24 11 02 00 00 	movl   $0x211,(%esp)
 267:	e8 fc ff ff ff       	call   268 <yadma_pcie_probe+0x268>
        pci_release_regions(pdev);
 26c:	89 d8                	mov    %ebx,%eax
 26e:	e8 fc ff ff ff       	call   26f <yadma_pcie_probe+0x26f>
        kfree(yadmaPrivData);
 273:	a1 00 00 00 00       	mov    0x0,%eax
 278:	e8 fc ff ff ff       	call   279 <yadma_pcie_probe+0x279>
        pci_disable_device(pdev);
 27d:	89 d8                	mov    %ebx,%eax
 27f:	e8 fc ff ff ff       	call   280 <yadma_pcie_probe+0x280>
        return pciRet;
 284:	e9 af 02 00 00       	jmp    538 <yadma_pcie_probe+0x538>
    } else {
        log_verbose(KERN_INFO "Set DMA mask as 32bits.\n");
 289:	c7 04 24 2d 02 00 00 	movl   $0x22d,(%esp)
 290:	e8 fc ff ff ff       	call   291 <yadma_pcie_probe+0x291>
     */
    for(i=0; i<MAX_BARS; i++) {
        u32 size;

        /* At least BAR0 must be there. */
        if ((size = pci_resource_len(pdev, i)) == 0) {
 295:	8b 83 cc 01 00 00    	mov    0x1cc(%ebx),%eax
 29b:	8b 93 d0 01 00 00    	mov    0x1d0(%ebx),%edx
 2a1:	8b 8b d4 01 00 00    	mov    0x1d4(%ebx),%ecx
 2a7:	09 c2                	or     %eax,%edx
 2a9:	74 0b                	je     2b6 <yadma_pcie_probe+0x2b6>
 2ab:	41                   	inc    %ecx
 2ac:	29 c1                	sub    %eax,%ecx
 2ae:	0f 84 24 01 00 00    	je     3d8 <yadma_pcie_probe+0x3d8>
 2b4:	eb 0f                	jmp    2c5 <yadma_pcie_probe+0x2c5>
 2b6:	8b 93 d8 01 00 00    	mov    0x1d8(%ebx),%edx
 2bc:	09 ca                	or     %ecx,%edx
 2be:	75 eb                	jne    2ab <yadma_pcie_probe+0x2ab>
 2c0:	e9 13 01 00 00       	jmp    3d8 <yadma_pcie_probe+0x3d8>
                continue;
            }
        }
        /* Set a bitmask for all the BARs that are present. */
        else
            (yadmaPrivData->bar_mask) |= ( 1 << i );
 2c5:	8b 35 00 00 00 00    	mov    0x0,%esi
 2cb:	83 4e 10 01          	orl    $0x1,0x10(%esi)

        /* Check all BARs for memory-mapped or I/O-mapped. The driver is
         * intended to be memory-mapped.
         */
        if (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM)) {
 2cf:	f6 83 e1 01 00 00 02 	testb  $0x2,0x1e1(%ebx)
 2d6:	0f 84 0d 01 00 00    	je     3e9 <yadma_pcie_probe+0x3e9>
            pci_disable_device(pdev);
            return YADMA_FAILURE;
        }

        /* Get base address of device memory and length for all BARs */
        yadmaPrivData->bar_info[i].bar_phys_addr = pci_resource_start(pdev, i);
 2dc:	8b 83 cc 01 00 00    	mov    0x1cc(%ebx),%eax
/*
 * The default ioremap() behavior is non-cached:
 */
static inline void __iomem *ioremap(resource_size_t offset, unsigned long size)
{
	return ioremap_nocache(offset, size);
 2e2:	31 d2                	xor    %edx,%edx
        yadmaPrivData->bar_info[i].bar_len = size;
 2e4:	89 4e 1c             	mov    %ecx,0x1c(%esi)
            pci_disable_device(pdev);
            return YADMA_FAILURE;
        }

        /* Get base address of device memory and length for all BARs */
        yadmaPrivData->bar_info[i].bar_phys_addr = pci_resource_start(pdev, i);
 2e7:	89 46 18             	mov    %eax,0x18(%esi)
 2ea:	e8 fc ff ff ff       	call   2eb <yadma_pcie_probe+0x2eb>
         * of memory, especially if users are sharing a BAR region. In
         * such a case, call ioremap for more number of smaller chunks
         * of memory. Or mapping should be done based on user request
         * with user size. Neither is being done now - maybe later.
         */
        if((yadmaPrivData->bar_info[i].bar_virt_addr =
 2ef:	85 c0                	test   %eax,%eax
 2f1:	89 46 20             	mov    %eax,0x20(%esi)
 2f4:	74 30                	je     326 <yadma_pcie_probe+0x326>
            log_verbose(KERN_ERR "Cannot map BAR %d space, invalidating.\n", i);
            (yadmaPrivData->bar_mask) &= ~( 1 << i );
        }
        else
        {
            log_verbose(KERN_INFO "ioremap: [BAR %d] Base PA %x Len %d VA %x\n", i,
 2f6:	a1 00 00 00 00       	mov    0x0,%eax
 2fb:	8b 50 20             	mov    0x20(%eax),%edx
 2fe:	89 54 24 10          	mov    %edx,0x10(%esp)
 302:	8b 50 1c             	mov    0x1c(%eax),%edx
 305:	89 54 24 0c          	mov    %edx,0xc(%esp)
 309:	8b 40 18             	mov    0x18(%eax),%eax
 30c:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
 313:	00 
 314:	c7 04 24 49 02 00 00 	movl   $0x249,(%esp)
 31b:	89 44 24 08          	mov    %eax,0x8(%esp)
 31f:	e8 fc ff ff ff       	call   320 <yadma_pcie_probe+0x320>
 324:	eb 1d                	jmp    343 <yadma_pcie_probe+0x343>
         * with user size. Neither is being done now - maybe later.
         */
        if((yadmaPrivData->bar_info[i].bar_virt_addr =
            ioremap((yadmaPrivData->bar_info[i].bar_phys_addr), size)) == 0UL)
        {
            log_verbose(KERN_ERR "Cannot map BAR %d space, invalidating.\n", i);
 326:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
 32d:	00 
 32e:	c7 04 24 77 02 00 00 	movl   $0x277,(%esp)
 335:	e8 fc ff ff ff       	call   336 <yadma_pcie_probe+0x336>
            (yadmaPrivData->bar_mask) &= ~( 1 << i );
 33a:	a1 00 00 00 00       	mov    0x0,%eax
 33f:	83 60 10 fe          	andl   $0xfffffffe,0x10(%eax)
                (u32) (yadmaPrivData->bar_info[i].bar_phys_addr),
                (u32) (yadmaPrivData->bar_info[i].bar_len),
                (u32) (yadmaPrivData->bar_info[i].bar_virt_addr));
        }
    }
    log_verbose(KERN_INFO "Bar mask is 0x%x\n", (yadmaPrivData->bar_mask));
 343:	a1 00 00 00 00       	mov    0x0,%eax
 348:	8b 40 10             	mov    0x10(%eax),%eax
 34b:	c7 04 24 a2 02 00 00 	movl   $0x2a2,(%esp)
 352:	89 44 24 04          	mov    %eax,0x4(%esp)
 356:	e8 fc ff ff ff       	call   357 <yadma_pcie_probe+0x357>

    /* Disable global interrupts */
    log_verbose(KERN_INFO "DMA interrupt disable.\n");
 35b:	c7 04 24 b7 02 00 00 	movl   $0x2b7,(%esp)
 362:	e8 fc ff ff ff       	call   363 <yadma_pcie_probe+0x363>
    Dma_mIntDisable(yadmaPrivData->bar_info[0].bar_virt_addr);
 367:	a1 00 00 00 00       	mov    0x0,%eax
 36c:	8b 40 20             	mov    0x20(%eax),%eax
 36f:	e8 fc ff ff ff       	call   370 <yadma_pcie_probe+0x370>
 374:	89 c2                	mov    %eax,%edx
 376:	a1 00 00 00 00       	mov    0x0,%eax
 37b:	83 e2 ee             	and    $0xffffffee,%edx
 37e:	8b 40 20             	mov    0x20(%eax),%eax
 381:	e8 fc ff ff ff       	call   382 <yadma_pcie_probe+0x382>

    yadmaPrivData->pdev=pdev;
 386:	a1 00 00 00 00       	mov    0x0,%eax
 38b:	89 18                	mov    %ebx,(%eax)

    /* Initialize DMA common registers? !!!! */


    /* Save private data pointer in device structure */
    log_verbose(KERN_INFO "Set pci drvdata.\n");
 38d:	c7 04 24 d2 02 00 00 	movl   $0x2d2,(%esp)
 394:	e8 fc ff ff ff       	call   395 <yadma_pcie_probe+0x395>
}

static inline void pci_set_drvdata(struct pci_dev *pdev, void *data)
{
	dev_set_drvdata(&pdev->dev, data);
 399:	8b 15 00 00 00 00    	mov    0x0,%edx
 39f:	8b 45 e0             	mov    -0x20(%ebp),%eax
 3a2:	e8 fc ff ff ff       	call   3a3 <yadma_pcie_probe+0x3a3>
    pci_set_drvdata(pdev, yadmaPrivData);


	/* Setup character device "/dev/yadma" */
    log_verbose(KERN_INFO "Setup char dev.\n");
 3a7:	c7 04 24 e7 02 00 00 	movl   $0x2e7,(%esp)
 3ae:	e8 fc ff ff ff       	call   3af <yadma_pcie_probe+0x3af>
	yadma_setup_cdev(yadmaPrivData);
 3b3:	8b 35 00 00 00 00    	mov    0x0,%esi
static void yadma_setup_cdev(PrivateDataStru* priv)
{
	int err;

    /* First allocate a major/minor number. */
    err = alloc_chrdev_region(&priv->yadma_dev, 0, 1, "yadma_chrdev");
 3b9:	31 d2                	xor    %edx,%edx
 3bb:	b9 01 00 00 00       	mov    $0x1,%ecx
 3c0:	8d 46 38             	lea    0x38(%esi),%eax
 3c3:	c7 04 24 fb 02 00 00 	movl   $0x2fb,(%esp)
 3ca:	e8 fc ff ff ff       	call   3cb <yadma_pcie_probe+0x3cb>
    if(IS_ERR((int *)err))
 3cf:	3d 00 f0 ff ff       	cmp    $0xfffff000,%eax
 3d4:	76 57                	jbe    42d <yadma_pcie_probe+0x42d>
 3d6:	eb 47                	jmp    41f <yadma_pcie_probe+0x41f>
        u32 size;

        /* At least BAR0 must be there. */
        if ((size = pci_resource_len(pdev, i)) == 0) {
            if (i == 0) {
                log_verbose(KERN_ERR "BAR %d not valid, aborting.\n", i);
 3d8:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
 3df:	00 
 3e0:	c7 04 24 08 03 00 00 	movl   $0x308,(%esp)
 3e7:	eb 0f                	jmp    3f8 <yadma_pcie_probe+0x3f8>

        /* Check all BARs for memory-mapped or I/O-mapped. The driver is
         * intended to be memory-mapped.
         */
        if (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM)) {
            log_verbose(KERN_ERR "BAR %d is of wrong type, aborting.\n", i);
 3e9:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
 3f0:	00 
 3f1:	c7 04 24 28 03 00 00 	movl   $0x328,(%esp)
 3f8:	e8 fc ff ff ff       	call   3f9 <yadma_pcie_probe+0x3f9>
            pci_release_regions(pdev);
 3fd:	89 d8                	mov    %ebx,%eax
 3ff:	e8 fc ff ff ff       	call   400 <yadma_pcie_probe+0x400>
            kfree(yadmaPrivData);
 404:	a1 00 00 00 00       	mov    0x0,%eax
 409:	e8 fc ff ff ff       	call   40a <yadma_pcie_probe+0x40a>
            pci_disable_device(pdev);
 40e:	89 d8                	mov    %ebx,%eax
 410:	e8 fc ff ff ff       	call   411 <yadma_pcie_probe+0x411>
            return YADMA_FAILURE;
 415:	be 01 00 00 00       	mov    $0x1,%esi
 41a:	e9 19 01 00 00       	jmp    538 <yadma_pcie_probe+0x538>
	int err;

    /* First allocate a major/minor number. */
    err = alloc_chrdev_region(&priv->yadma_dev, 0, 1, "yadma_chrdev");
    if(IS_ERR((int *)err))
        log_verbose(KERN_ERR "Error allocating char device region\n");
 41f:	c7 04 24 4f 03 00 00 	movl   $0x34f,(%esp)
 426:	e8 fc ff ff ff       	call   427 <yadma_pcie_probe+0x427>
 42b:	eb 74                	jmp    4a1 <yadma_pcie_probe+0x4a1>
    else
    {
        /* Register our character device */
        priv->yadma_cdev = cdev_alloc();
 42d:	e8 fc ff ff ff       	call   42e <yadma_pcie_probe+0x42e>
        if(IS_ERR(priv->yadma_cdev))
 432:	3d 00 f0 ff ff       	cmp    $0xfffff000,%eax
    if(IS_ERR((int *)err))
        log_verbose(KERN_ERR "Error allocating char device region\n");
    else
    {
        /* Register our character device */
        priv->yadma_cdev = cdev_alloc();
 437:	89 46 34             	mov    %eax,0x34(%esi)
        if(IS_ERR(priv->yadma_cdev))
 43a:	76 09                	jbe    445 <yadma_pcie_probe+0x445>
        {
            log_verbose(KERN_ERR "Alloc error registering device driver\n");
 43c:	c7 04 24 77 03 00 00 	movl   $0x377,(%esp)
 443:	eb 4a                	jmp    48f <yadma_pcie_probe+0x48f>
            unregister_chrdev_region(priv->yadma_dev, 1);
            err = -1;
        }
        else
        {
            priv->yadma_cdev->owner = THIS_MODULE;
 445:	c7 40 24 00 00 00 00 	movl   $0x0,0x24(%eax)
            priv->yadma_cdev->ops = &yadma_cdev_file_ops;
 44c:	8b 46 34             	mov    0x34(%esi),%eax
            priv->yadma_cdev->dev = priv->yadma_dev;
            err = cdev_add(priv->yadma_cdev, priv->yadma_dev, 1);
 44f:	b9 01 00 00 00       	mov    $0x1,%ecx
            err = -1;
        }
        else
        {
            priv->yadma_cdev->owner = THIS_MODULE;
            priv->yadma_cdev->ops = &yadma_cdev_file_ops;
 454:	c7 40 28 b0 00 00 00 	movl   $0xb0,0x28(%eax)
            priv->yadma_cdev->dev = priv->yadma_dev;
 45b:	8b 46 34             	mov    0x34(%esi),%eax
 45e:	8b 56 38             	mov    0x38(%esi),%edx
 461:	89 50 34             	mov    %edx,0x34(%eax)
            err = cdev_add(priv->yadma_cdev, priv->yadma_dev, 1);
 464:	8b 56 38             	mov    0x38(%esi),%edx
 467:	8b 46 34             	mov    0x34(%esi),%eax
 46a:	e8 fc ff ff ff       	call   46b <yadma_pcie_probe+0x46b>
 46f:	89 c7                	mov    %eax,%edi
            log_verbose(KERN_INFO "Allocate and add char dev  %d\n", priv->yadma_dev);
 471:	8b 46 38             	mov    0x38(%esi),%eax
 474:	c7 04 24 a1 03 00 00 	movl   $0x3a1,(%esp)
 47b:	89 44 24 04          	mov    %eax,0x4(%esp)
 47f:	e8 fc ff ff ff       	call   480 <yadma_pcie_probe+0x480>

            if(err < 0)
 484:	85 ff                	test   %edi,%edi
 486:	79 19                	jns    4a1 <yadma_pcie_probe+0x4a1>
            {
                log_verbose(KERN_ERR "Error, then unregistering the char dev.\n");
 488:	c7 04 24 c3 03 00 00 	movl   $0x3c3,(%esp)
 48f:	e8 fc ff ff ff       	call   490 <yadma_pcie_probe+0x490>
                unregister_chrdev_region(priv->yadma_dev, 1);
 494:	8b 46 38             	mov    0x38(%esi),%eax
 497:	ba 01 00 00 00       	mov    $0x1,%edx
 49c:	e8 fc ff ff ff       	call   49d <yadma_pcie_probe+0x49d>
    log_verbose(KERN_INFO "Setup char dev.\n");
	yadma_setup_cdev(yadmaPrivData);

    if(!IS_ERR((int *)chrRet))
    {
		log_verbose(KERN_INFO "Device registered with major number %d\n",
 4a1:	a1 00 00 00 00       	mov    0x0,%eax
    Dma_mIntEnable(yadmaPrivData->bar_info[0].bar_virt_addr);

#endif

    log_verbose("End of probe\n");
	return 0;
 4a6:	31 f6                	xor    %esi,%esi
    log_verbose(KERN_INFO "Setup char dev.\n");
	yadma_setup_cdev(yadmaPrivData);

    if(!IS_ERR((int *)chrRet))
    {
		log_verbose(KERN_INFO "Device registered with major number %d\n",
 4a8:	8b 40 38             	mov    0x38(%eax),%eax
 4ab:	c7 04 24 ef 03 00 00 	movl   $0x3ef,(%esp)
 4b2:	c1 e8 14             	shr    $0x14,%eax
 4b5:	89 44 24 04          	mov    %eax,0x4(%esp)
 4b9:	e8 fc ff ff ff       	call   4ba <yadma_pcie_probe+0x4ba>

		}


        /* Start stats polling routine */
        log_verbose(KERN_INFO "probe: Starting stats timer %p after %d\n",
 4be:	c7 44 24 08 fa 00 00 	movl   $0xfa,0x8(%esp)
 4c5:	00 
 4c6:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
 4cd:	00 
 4ce:	c7 04 24 1a 04 00 00 	movl   $0x41a,(%esp)
 4d5:	e8 fc ff ff ff       	call   4d6 <yadma_pcie_probe+0x4d6>
                                            &stats_timer, HZ);
        /* Now start timer */
        init_timer(&stats_timer);
 4da:	31 c9                	xor    %ecx,%ecx
 4dc:	31 d2                	xor    %edx,%edx
 4de:	b8 00 00 00 00       	mov    $0x0,%eax
 4e3:	e8 fc ff ff ff       	call   4e4 <yadma_pcie_probe+0x4e4>
        stats_timer.expires=jiffies + HZ;
 4e8:	a1 00 00 00 00       	mov    0x0,%eax
        stats_timer.data=(unsigned long) pdev;
 4ed:	89 1d 14 00 00 00    	mov    %ebx,0x14
        stats_timer.function = yadma_stats;
 4f3:	c7 05 10 00 00 00 00 	movl   $0x0,0x10
 4fa:	00 00 00 
        /* Start stats polling routine */
        log_verbose(KERN_INFO "probe: Starting stats timer %p after %d\n",
                                            &stats_timer, HZ);
        /* Now start timer */
        init_timer(&stats_timer);
        stats_timer.expires=jiffies + HZ;
 4fd:	05 fa 00 00 00       	add    $0xfa,%eax
 502:	a3 08 00 00 00       	mov    %eax,0x8
        stats_timer.data=(unsigned long) pdev;
        stats_timer.function = yadma_stats;
        add_timer(&stats_timer);
 507:	b8 00 00 00 00       	mov    $0x0,%eax
 50c:	e8 fc ff ff ff       	call   50d <yadma_pcie_probe+0x50d>
    }

    yadmaDriverState = YADMA_INITIALIZED;
 511:	c7 05 78 00 00 00 01 	movl   $0x1,0x78
 518:	00 00 00 
    log_verbose("Value of HZ is %d\n", HZ);
    Dma_mIntEnable(yadmaPrivData->bar_info[0].bar_virt_addr);

#endif

    log_verbose("End of probe\n");
 51b:	c7 04 24 46 04 00 00 	movl   $0x446,(%esp)
 522:	e8 fc ff ff ff       	call   523 <yadma_pcie_probe+0x523>
	return 0;
 527:	eb 0f                	jmp    538 <yadma_pcie_probe+0x538>

	if (!ops->alloc)
 529:	8b 3f                	mov    (%edi),%edi
 52b:	85 ff                	test   %edi,%edi
 52d:	0f 85 7a fb ff ff    	jne    ad <yadma_pcie_probe+0xad>
 533:	e9 b1 fb ff ff       	jmp    e9 <yadma_pcie_probe+0xe9>
out_release_attr_group:

out_release_irq:
	free_irq(pdev->irq, pdev);

}
 538:	83 c4 30             	add    $0x30,%esp
 53b:	89 f0                	mov    %esi,%eax
 53d:	5b                   	pop    %ebx
 53e:	5e                   	pop    %esi
 53f:	5f                   	pop    %edi
 540:	5d                   	pop    %ebp
 541:	c3                   	ret    

Disassembly of section .devexit.text:

00000000 <yadma_remove>:

static void __devexit  yadma_remove(struct pci_dev *pdev)
{
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	57                   	push   %edi
 * driver-specific data.  They are really just a wrapper around
 * the generic device structure functions of these calls.
 */
static inline void *pci_get_drvdata(struct pci_dev *pdev)
{
	return dev_get_drvdata(&pdev->dev);
   4:	bf e9 03 00 00       	mov    $0x3e9,%edi
   9:	56                   	push   %esi
   a:	53                   	push   %ebx
   b:	89 c3                	mov    %eax,%ebx
   d:	83 ec 0c             	sub    $0xc,%esp
#ifdef FIFO_EMPTY_CHECK
    u32 barBase = (u32)(yadmaPrivData->bar_info[0].bar_virt_addr);

#endif

    log_verbose("Came to yadma_remove\n");
  10:	c7 04 24 b1 04 00 00 	movl   $0x4b1,(%esp)
  17:	8d 73 60             	lea    0x60(%ebx),%esi
  1a:	e8 fc ff ff ff       	call   1b <yadma_remove+0x1b>
  1f:	89 f0                	mov    %esi,%eax
  21:	e8 fc ff ff ff       	call   22 <yadma_remove+0x22>
  26:	eb 0a                	jmp    32 <yadma_remove+0x32>
    lp = pci_get_drvdata(pdev);

    /* The driver state flag has already been changed */

    mdelay(1000);
  28:	b8 58 89 41 00       	mov    $0x418958,%eax
  2d:	e8 fc ff ff ff       	call   2e <yadma_remove+0x2e>
  32:	4f                   	dec    %edi
  33:	75 f3                	jne    28 <yadma_remove+0x28>
	raw_spin_lock(&lock->rlock);
}

static inline void spin_lock_bh(spinlock_t *lock)
{
	raw_spin_lock_bh(&lock->rlock);
  35:	b8 74 00 00 00       	mov    $0x74,%eax
  3a:	e8 fc ff ff ff       	call   3b <yadma_remove+0x3b>

    /* Stop the polling routines */
    spin_lock_bh(&DmaStatsLock);
    log_verbose(KERN_INFO "Disable stats timer.\n");
  3f:	c7 04 24 c7 04 00 00 	movl   $0x4c7,(%esp)
  46:	e8 fc ff ff ff       	call   47 <yadma_remove+0x47>
    del_timer_sync(&stats_timer);
  4b:	b8 00 00 00 00       	mov    $0x0,%eax
  50:	e8 fc ff ff ff       	call   51 <yadma_remove+0x51>
	raw_spin_unlock(&lock->rlock);
}

static inline void spin_unlock_bh(spinlock_t *lock)
{
	raw_spin_unlock_bh(&lock->rlock);
  55:	b8 74 00 00 00       	mov    $0x74,%eax
  5a:	e8 fc ff ff ff       	call   5b <yadma_remove+0x5b>
	raw_spin_lock(&lock->rlock);
}

static inline void spin_lock_bh(spinlock_t *lock)
{
	raw_spin_lock_bh(&lock->rlock);
  5f:	b8 70 00 00 00       	mov    $0x70,%eax
  64:	e8 fc ff ff ff       	call   65 <yadma_remove+0x65>
	raw_spin_unlock(&lock->rlock);
}

static inline void spin_unlock_bh(spinlock_t *lock)
{
	raw_spin_unlock_bh(&lock->rlock);
  69:	b8 70 00 00 00       	mov    $0x70,%eax
  6e:	e8 fc ff ff ff       	call   6f <yadma_remove+0x6f>
	raw_spin_lock(&lock->rlock);
}

static inline void spin_lock_bh(spinlock_t *lock)
{
	raw_spin_lock_bh(&lock->rlock);
  73:	b8 70 00 00 00       	mov    $0x70,%eax
  78:	e8 fc ff ff ff       	call   79 <yadma_remove+0x79>

#endif

    for(i=0; i<MAX_BARS; i++)
    {
        if((yadmaPrivData->bar_mask) & ( 1 << i )) {
  7d:	a1 00 00 00 00       	mov    0x0,%eax
  82:	f6 40 10 01          	testb  $0x1,0x10(%eax)
  86:	74 28                	je     b0 <yadma_remove+0xb0>
            log_verbose(KERN_INFO "iounmap: BAR %d virt = %p.\n", i, yadmaPrivData->bar_info[i].bar_virt_addr);
  88:	8b 40 20             	mov    0x20(%eax),%eax
  8b:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
  92:	00 
  93:	c7 04 24 e0 04 00 00 	movl   $0x4e0,(%esp)
  9a:	89 44 24 08          	mov    %eax,0x8(%esp)
  9e:	e8 fc ff ff ff       	call   9f <yadma_remove+0x9f>
            iounmap(yadmaPrivData->bar_info[i].bar_virt_addr);
  a3:	a1 00 00 00 00       	mov    0x0,%eax
  a8:	8b 40 20             	mov    0x20(%eax),%eax
  ab:	e8 fc ff ff ff       	call   ac <yadma_remove+0xac>
	raw_spin_unlock(&lock->rlock);
}

static inline void spin_unlock_bh(spinlock_t *lock)
{
	raw_spin_unlock_bh(&lock->rlock);
  b0:	b8 70 00 00 00       	mov    $0x70,%eax
  b5:	e8 fc ff ff ff       	call   b6 <yadma_remove+0xb6>
        }
    }
    spin_unlock_bh(&DmaLock);

    if(yadmaPrivData->yadma_cdev != NULL)
  ba:	a1 00 00 00 00       	mov    0x0,%eax
  bf:	83 78 34 00          	cmpl   $0x0,0x34(%eax)
  c3:	74 32                	je     f7 <yadma_remove+0xf7>
    {
		log_verbose("Unregistering char device driver %d\n", yadmaPrivData->yadma_dev);
  c5:	8b 40 38             	mov    0x38(%eax),%eax
  c8:	c7 04 24 ff 04 00 00 	movl   $0x4ff,(%esp)
  cf:	89 44 24 04          	mov    %eax,0x4(%esp)
  d3:	e8 fc ff ff ff       	call   d4 <yadma_remove+0xd4>
		cdev_del(yadmaPrivData->yadma_cdev);
  d8:	a1 00 00 00 00       	mov    0x0,%eax
  dd:	8b 40 34             	mov    0x34(%eax),%eax
  e0:	e8 fc ff ff ff       	call   e1 <yadma_remove+0xe1>
		unregister_chrdev_region(yadmaPrivData->yadma_dev, 1);
  e5:	a1 00 00 00 00       	mov    0x0,%eax
  ea:	ba 01 00 00 00       	mov    $0x1,%edx
  ef:	8b 40 38             	mov    0x38(%eax),%eax
  f2:	e8 fc ff ff ff       	call   f3 <yadma_remove+0xf3>
    }

	log_verbose(KERN_INFO "PCI release regions and disable device.\n");
  f7:	c7 04 24 24 05 00 00 	movl   $0x524,(%esp)
  fe:	e8 fc ff ff ff       	call   ff <yadma_remove+0xff>
	pci_release_regions(pdev);
 103:	89 d8                	mov    %ebx,%eax
 105:	e8 fc ff ff ff       	call   106 <yadma_remove+0x106>
	pci_disable_device(pdev);
 10a:	89 d8                	mov    %ebx,%eax
 10c:	e8 fc ff ff ff       	call   10d <yadma_remove+0x10d>
}

static inline void pci_set_drvdata(struct pci_dev *pdev, void *data)
{
	dev_set_drvdata(&pdev->dev, data);
 111:	31 d2                	xor    %edx,%edx
 113:	89 f0                	mov    %esi,%eax
 115:	e8 fc ff ff ff       	call   116 <yadma_remove+0x116>
	pci_set_drvdata(pdev, NULL);

	/* unregister sysfs files when driver is removed */
    log_verbose(KERN_INFO "unregister sysfs files.\n");
 11a:	c7 04 24 50 05 00 00 	movl   $0x550,(%esp)
 121:	e8 fc ff ff ff       	call   122 <yadma_remove+0x122>
	unregister_sysfs_files(&pdev->dev.kobj);
 126:	8d 43 68             	lea    0x68(%ebx),%eax

    /* Reset DMA - this includes disabling interrupts and DMA. */
	log_verbose(KERN_INFO "Destroy DMA channels...\n");
    for(i=0; i<MAX_CHANS; i++)
 129:	31 db                	xor    %ebx,%ebx
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);

	/* unregister sysfs files when driver is removed */
    log_verbose(KERN_INFO "unregister sysfs files.\n");
	unregister_sysfs_files(&pdev->dev.kobj);
 12b:	e8 fc ff ff ff       	call   12c <yadma_remove+0x12c>

    /* Reset DMA - this includes disabling interrupts and DMA. */
	log_verbose(KERN_INFO "Destroy DMA channels...\n");
 130:	c7 04 24 6c 05 00 00 	movl   $0x56c,(%esp)
 137:	e8 fc ff ff ff       	call   138 <yadma_remove+0x138>
    for(i=0; i<MAX_CHANS; i++)
    {
		yadma_destroy_channel(&(pdev->dev), yadmaPrivData->dma_chans[i]);
 13c:	a1 00 00 00 00       	mov    0x0,%eax
 141:	8b 54 98 24          	mov    0x24(%eax,%ebx,4),%edx
 */

static void yadma_destroy_channel(struct device *dev, DmaChannel* chan)
{

	if(chan) {
 145:	85 d2                	test   %edx,%edx
 147:	74 07                	je     150 <yadma_remove+0x150>
 149:	89 f0                	mov    %esi,%eax
 14b:	e8 fc ff ff ff       	call   14c <yadma_remove+0x14c>
    /* Reset DMA - this includes disabling interrupts and DMA. */
	log_verbose(KERN_INFO "Destroy DMA channels...\n");
    for(i=0; i<MAX_CHANS; i++)
    {
		yadma_destroy_channel(&(pdev->dev), yadmaPrivData->dma_chans[i]);
		yadmaPrivData->dma_chans[i] = NULL;
 150:	a1 00 00 00 00       	mov    0x0,%eax
 155:	c7 44 98 24 00 00 00 	movl   $0x0,0x24(%eax,%ebx,4)
 15c:	00 
    log_verbose(KERN_INFO "unregister sysfs files.\n");
	unregister_sysfs_files(&pdev->dev.kobj);

    /* Reset DMA - this includes disabling interrupts and DMA. */
	log_verbose(KERN_INFO "Destroy DMA channels...\n");
    for(i=0; i<MAX_CHANS; i++)
 15d:	43                   	inc    %ebx
 15e:	83 fb 04             	cmp    $0x4,%ebx
 161:	75 d9                	jne    13c <yadma_remove+0x13c>
    {
		yadma_destroy_channel(&(pdev->dev), yadmaPrivData->dma_chans[i]);
		yadmaPrivData->dma_chans[i] = NULL;
    }
}
 163:	83 c4 0c             	add    $0xc,%esp
 166:	5b                   	pop    %ebx
 167:	5e                   	pop    %esi
 168:	5f                   	pop    %edi
 169:	5d                   	pop    %ebp
 16a:	c3                   	ret    

Disassembly of section .init.text:

00000000 <init_module>:
	/* Nerver call: nlmsg_free(skb_out); */
}


static int __init yadma_init(void)
{
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 08             	sub    $0x8,%esp
	int index = kmalloc_index(size);

	if (index == 0)
		return NULL;

	return kmalloc_caches[index];
   6:	a1 08 00 00 00       	mov    0x8,%eax
    int i;
  /* Initialize the locks */
  spin_lock_init(&DmaLock);
   b:	66 c7 05 70 00 00 00 	movw   $0x0,0x70
  12:	00 00 
  spin_lock_init(&IntrLock);
  14:	66 c7 05 72 00 00 00 	movw   $0x0,0x72
  1b:	00 00 
  spin_lock_init(&DmaStatsLock);
  1d:	66 c7 05 74 00 00 00 	movw   $0x0,0x74
  24:	00 00 
			return kmalloc_large(size, flags);

		if (!(flags & SLUB_DMA)) {
			struct kmem_cache *s = kmalloc_slab(size);

			if (!s)
  26:	85 c0                	test   %eax,%eax
  28:	74 11                	je     3b <init_module+0x3b>
				return ZERO_SIZE_PTR;

			return kmem_cache_alloc_trace(s, flags, size);
  2a:	b9 88 00 00 00       	mov    $0x88,%ecx
  2f:	ba d0 00 00 00       	mov    $0xd0,%edx
  34:	e8 fc ff ff ff       	call   35 <init_module+0x35>
  39:	eb 05                	jmp    40 <init_module+0x40>

		if (!(flags & SLUB_DMA)) {
			struct kmem_cache *s = kmalloc_slab(size);

			if (!s)
				return ZERO_SIZE_PTR;
  3b:	b8 10 00 00 00       	mov    $0x10,%eax

    /* Allocate space for holding driver-private data - for storing driver
     * context.
     */
    yadmaPrivData = kmalloc(sizeof(PrivateDataStru), GFP_KERNEL);
    if(yadmaPrivData == NULL)
  40:	85 c0                	test   %eax,%eax
  spin_lock_init(&DmaStatsLock);

    /* Allocate space for holding driver-private data - for storing driver
     * context.
     */
    yadmaPrivData = kmalloc(sizeof(PrivateDataStru), GFP_KERNEL);
  42:	a3 00 00 00 00       	mov    %eax,0x0
    if(yadmaPrivData == NULL)
  47:	75 13                	jne    5c <init_module+0x5c>
    {
        log_verbose(KERN_ERR "Unable to allocate YADMA private data.\n");
  49:	c7 04 24 e7 05 00 00 	movl   $0x5e7,(%esp)
  50:	e8 fc ff ff ff       	call   51 <init_module+0x51>
        return YADMA_FAILURE;
  55:	b8 01 00 00 00       	mov    $0x1,%eax
  5a:	eb 77                	jmp    d3 <init_module+0xd3>
    }

	log_verbose("yadmaPrivData at %p\n", yadmaPrivData);
  5c:	89 44 24 04          	mov    %eax,0x4(%esp)
  60:	c7 04 24 12 06 00 00 	movl   $0x612,(%esp)
  67:	e8 fc ff ff ff       	call   68 <init_module+0x68>

  init_timer(&demo_timer);
  6c:	31 c9                	xor    %ecx,%ecx
  6e:	31 d2                	xor    %edx,%edx
  70:	b8 00 00 00 00       	mov    $0x0,%eax
  75:	e8 fc ff ff ff       	call   76 <init_module+0x76>
  demo_timer.expires=jiffies + HZ;
  7a:	a1 00 00 00 00       	mov    0x0,%eax
  demo_timer.function = yadma_demo;
  7f:	c7 05 10 00 00 00 50 	movl   $0x50,0x10
  86:	00 00 00 
    }

	log_verbose("yadmaPrivData at %p\n", yadmaPrivData);

  init_timer(&demo_timer);
  demo_timer.expires=jiffies + HZ;
  89:	05 fa 00 00 00       	add    $0xfa,%eax
  8e:	a3 08 00 00 00       	mov    %eax,0x8
  demo_timer.function = yadma_demo;
  add_timer(&demo_timer);
  93:	b8 00 00 00 00       	mov    $0x0,%eax
  98:	e8 fc ff ff ff       	call   99 <init_module+0x99>

  /* Initialize the netlink socket */
  netlink_init();
  9d:	e8 fc ff ff ff       	call   9e <init_module+0x9e>

  /* Register procfs files */
  log_verbose(KERN_INFO "register proc files.\n");
  a2:	c7 04 24 27 06 00 00 	movl   $0x627,(%esp)
  a9:	e8 fc ff ff ff       	call   aa <init_module+0xaa>
  register_proc_files();
  ae:	e8 fc ff ff ff       	call   af <init_module+0xaf>

  /* Just register the driver. No kernel boot options used. */
  log_verbose(KERN_INFO "Inserting YADMA driver in kernel.\n");
  b3:	c7 04 24 40 06 00 00 	movl   $0x640,(%esp)
  ba:	e8 fc ff ff ff       	call   bb <init_module+0xbb>
    return pci_register_driver(&yadma_driver);
  bf:	b9 c7 01 00 00       	mov    $0x1c7,%ecx
  c4:	ba 00 00 00 00       	mov    $0x0,%edx
  c9:	b8 3c 00 00 00       	mov    $0x3c,%eax
  ce:	e8 fc ff ff ff       	call   cf <init_module+0xcf>
}
  d3:	c9                   	leave  
  d4:	c3                   	ret    

Disassembly of section .exit.text:

00000000 <cleanup_module>:

static void __exit yadma_cleanup(void)
{
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	53                   	push   %ebx
   4:	83 ec 08             	sub    $0x8,%esp

    int oldstate, i;

    log_verbose("Came to yadma_cleanup\n");
   7:	c7 04 24 66 06 00 00 	movl   $0x666,(%esp)
   e:	e8 fc ff ff ff       	call   f <cleanup_module+0xf>

    del_timer_sync(&demo_timer);
  13:	b8 00 00 00 00       	mov    $0x0,%eax
  18:	e8 fc ff ff ff       	call   19 <cleanup_module+0x19>
	raw_spin_lock(&lock->rlock);
}

static inline void spin_lock_bh(spinlock_t *lock)
{
	raw_spin_lock_bh(&lock->rlock);
  1d:	b8 70 00 00 00       	mov    $0x70,%eax

    /* First, change the driver state - so that other entry points
     * will not make a difference from this point on.
     */
    oldstate = yadmaDriverState;
  22:	8b 1d 78 00 00 00    	mov    0x78,%ebx
  28:	e8 fc ff ff ff       	call   29 <cleanup_module+0x29>
	raw_spin_unlock(&lock->rlock);
}

static inline void spin_unlock_bh(spinlock_t *lock)
{
	raw_spin_unlock_bh(&lock->rlock);
  2d:	b8 70 00 00 00       	mov    $0x70,%eax
    spin_lock_bh(&DmaLock);
    yadmaDriverState = YADMA_UNINITIALIZED;
  32:	c7 05 78 00 00 00 00 	movl   $0x0,0x78
  39:	00 00 00 
  3c:	e8 fc ff ff ff       	call   3d <cleanup_module+0x3d>
    spin_unlock_bh(&DmaLock);

    /* Then, unregister driver with PCI in order to free up resources */
    log_verbose(KERN_INFO "pci unregister driver.\n");
  41:	c7 04 24 7d 06 00 00 	movl   $0x67d,(%esp)
  48:	e8 fc ff ff ff       	call   49 <cleanup_module+0x49>
    pci_unregister_driver(&yadma_driver);
  4d:	b8 3c 00 00 00       	mov    $0x3c,%eax
  52:	e8 fc ff ff ff       	call   53 <cleanup_module+0x53>

    if(yadmaPrivData != NULL)
  57:	83 3d 00 00 00 00 00 	cmpl   $0x0,0x0
  5e:	74 21                	je     81 <cleanup_module+0x81>
    {
		log_verbose("GUI user open? %d\n", yadmaUserOpen);
  60:	a1 7c 00 00 00       	mov    0x7c,%eax
  65:	c7 04 24 98 06 00 00 	movl   $0x698,(%esp)
  6c:	89 44 24 04          	mov    %eax,0x4(%esp)
  70:	e8 fc ff ff ff       	call   71 <cleanup_module+0x71>
		kfree(yadmaPrivData);
  75:	a1 00 00 00 00       	mov    0x0,%eax
  7a:	e8 fc ff ff ff       	call   7b <cleanup_module+0x7b>
  7f:	eb 10                	jmp    91 <cleanup_module+0x91>
    }
    else
        log_verbose("yadmaDriverState still %d\n", oldstate);
  81:	89 5c 24 04          	mov    %ebx,0x4(%esp)
  85:	c7 04 24 ab 06 00 00 	movl   $0x6ab,(%esp)
  8c:	e8 fc ff ff ff       	call   8d <cleanup_module+0x8d>

	/* destroy netlink socket */
	netlink_destroy();
  91:	e8 fc ff ff ff       	call   92 <cleanup_module+0x92>

	/* remove procfs files */
	unregister_proc_files();
  96:	e8 fc ff ff ff       	call   97 <cleanup_module+0x97>
}
  9b:	58                   	pop    %eax
  9c:	5a                   	pop    %edx
  9d:	5b                   	pop    %ebx
  9e:	5d                   	pop    %ebp
  9f:	c3                   	ret    
